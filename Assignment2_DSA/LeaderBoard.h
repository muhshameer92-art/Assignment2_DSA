#pragma once
#include<iostream>
#include "person.h"
#include "vector.h"
using namespace std;
struct compositeKey {
	int score;
	int level;
	int ID;
	compositeKey(int s = 0, int lvl = 0, int id = 0) {
		score = s;
		level = lvl;
		ID = id;
	}
	bool operator==(const compositeKey& key) const {
		return score == key.score &&
			level == key.level &&
			ID == key.ID;
	}

	bool operator<(const compositeKey& key) const {
		if (score != key.score)
			return score < key.score;

		if (level != key.level)
			return level < key.level;

		return ID < key.ID;
	}

	bool operator>(const compositeKey& key) const {
		return key < *this;
	}
};
class leaderBoard {
	struct scoreCard {
		person* player;
		scoreCard* left;
		scoreCard* right;
		compositeKey key;
		int height;
		scoreCard(person* p = NULL, scoreCard* l = NULL, scoreCard* r = NULL) {
			player = p;
			left = l;
			right = r;
			height = 0;
			//composite key
			if (p) {
				key.ID = p->getPlayerID();
				key.level = p->getLvl();
				key.score = p->getScore();
			}
		}
	};
	scoreCard* root;
	int size;
	void clear(scoreCard* node) {
		if (!node)
			return;

		clear(node->left);
		clear(node->right);
		delete node;
		node = NULL;
	}
	int getH(scoreCard* node) {
		if (!node)
			return -1;
		return node->height;
	}
	void updateH(scoreCard* node) {
		node->height = 1 + max(getH(node->left), getH(node->right));
	}
	int BF(scoreCard* node) {
		if (!node) {
			return 0;
		}
		return getH(node->left) - getH(node->right);
	}
	bool isBalanced(scoreCard* node) {
		if (abs(BF(node)) > 1)
			return false;
		return true;
	}
	scoreCard* rotateRight(scoreCard* x) {
		if (x == nullptr || x->left == nullptr)
			return x;

		scoreCard* y = x->left;
		scoreCard* T2 = y->right;

		// Perform rotation
		y->right = x;
		x->left = T2;

		// Update heights
		updateH(x);
		updateH(y);
		return y;
	}
	scoreCard* rotateLeft(scoreCard* x) {
		if (x == nullptr || x->right == nullptr)
			return x;

		scoreCard* y = x->right;
		scoreCard* T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		updateH(x);
		updateH(y);

		return y;
	}
	scoreCard* doubleRotateRight(scoreCard* x) {
		if (x == nullptr)
			return x;

		x->left = rotateLeft(x->left);
		return rotateRight(x);
	}
	scoreCard* doubleRotateLeft(scoreCard* x) {
		if (x == nullptr)
			return x;

		x->right = rotateRight(x->right);
		return rotateLeft(x);
	}
	scoreCard* balance(scoreCard* node)
	{
		if (!node)
			return nullptr;

		updateH(node);

		int bf = BF(node);

		// LL
		if (bf > 1 && BF(node->left) >= 0)
			return rotateRight(node);

		// RR
		else if (bf < -1 && BF(node->right) <= 0)
			return rotateLeft(node);

		// LR
		else if (bf > 1 && BF(node->left) < 0)
			return doubleRotateRight(node);

		// RL
		else if (bf < -1 && BF(node->right) > 0)
			return doubleRotateLeft(node);

		return node;
	}
	scoreCard* insertHelper(scoreCard* node, person* p) {
		//edge case
		if (!p) {
			return node;
		}
		// base case
		if (!node) {
			size++;
			return new scoreCard(p);
		}
		compositeKey newKey (p->getScore(), p->getLvl(), p->getPlayerID());

		if (node->key > newKey)
			node->left = insertHelper(node->left, p);
		else if (node->key < newKey)
			node->right = insertHelper(node->right, p);
		else
			return node;
		//balance check - during backtracking - leaf node towards root
		return balance(node);
	}
	
	scoreCard* findMax(scoreCard* node) {
		if (!node)
			return NULL;
		if (!node->right)
			return node;
		return findMax(node->right);
	}
	scoreCard* findMin(scoreCard* node) {
		if (!node)
			return NULL;
		if (!node->left)
			return node;
		return findMin(node->left);
	}
	scoreCard* removeKeyHelper(scoreCard* node, compositeKey key)
	{
		if (!node)
			return nullptr;

		if (key < node->key)
			node->left = removeKeyHelper(node->left, key);

		else if (key > node->key)
			node->right = removeKeyHelper(node->right, key);

		else {
			if (!node->left || !node->right) {
				scoreCard* temp = node->left ?
					node->left : node->right;

				delete node;
				size--;
				return temp;
			}

			scoreCard* temp = findMax(node->left);

			node->player = temp->player;
			node->key = temp->key;

			node->left = removeKeyHelper(node->left, temp->key);
		}

		return balance(node);
	}
	scoreCard* removeHelper(scoreCard* node, person* p)
	{
		if (!node || !p)
			return node;

		compositeKey key(
			p->getScore(),
			p->getLvl(),
			p->getPlayerID()
		);

		if (key < node->key)
			node->left = removeHelper(node->left, p);

		else if (key > node->key)
			node->right = removeHelper(node->right, p);

		else {
			if (!node->left || !node->right) {
				scoreCard* temp = node->left ?
					node->left : node->right;

				delete node;
				size--;
				return temp;
			}

			scoreCard* temp = findMax(node->left);

			node->player = temp->player;
			node->key = temp->key;

			node->left = removeKeyHelper(node->left, temp->key);
		}

		return balance(node);
	}
	scoreCard* predecessor(compositeKey key) {
		scoreCard* current = root;
		scoreCard* pred = nullptr;

		while (current != nullptr) {
			if (current->key < key) {
				pred = current;
				current = current->right;
			}
			else {
				current = current->left;
			}
		}

		return pred;
	}

	scoreCard* successor(compositeKey key) {
		scoreCard* current = root;
		scoreCard* succ = nullptr;

		while (current != nullptr) {
			if (current->key > key) {
				succ = current;
				current = current->left;
			}
			else {
				current = current->right;
			}
		}

		return succ;
	}
	scoreCard* findByID(scoreCard* node, int playerID) {
		if (node == nullptr)
			return nullptr;

		if (node->player->getPlayerID() == playerID)
			return node;

		scoreCard* found = findByID(node->left, playerID);

		if (found != nullptr)
			return found;

		return findByID(node->right, playerID);
	}
	vector<person*> K_nearby_Helper(int playerID, int k) {

		vector<person*> nearby;

		if (k <= 0 || root == nullptr)
			return nearby;

		// Find target player
		scoreCard* target = findByID(root, playerID);

		if (target == nullptr)
			return nearby;

		// Find neighbours on both sides
		scoreCard* pred = predecessor(target->key);
		scoreCard* succ = successor(target->key);

		while (k > 0 && (pred != nullptr || succ != nullptr)) {

			if (pred == nullptr) {
				nearby.push_back(succ->player);
				succ = successor(succ->key);
			}
			else if (succ == nullptr) {
				nearby.push_back(pred->player);
				pred = predecessor(pred->key);
			}
			else {
				int targetScore = target->key.score;

				int predDiff = abs(targetScore - pred->key.score);
				int succDiff = abs(targetScore - succ->key.score);

				if (predDiff <= succDiff) {
					nearby.push_back(pred->player);
					pred = predecessor(pred->key);
				}
				else {
					nearby.push_back(succ->player);
					succ = successor(succ->key);
				}
			}

			k--;
		}

		return nearby;
	}
	void printInorder(scoreCard* node) {
		if (!node)
			return;
		printInorder(node->left);
		cout << *node->player << endl;
		printInorder(node->right);
	}
	void printInReverse(scoreCard* node) {
		if (!node)
			return;
		printInReverse(node->right);
		cout << *node->player << endl;
		printInReverse(node->left);
	}
public:
	leaderBoard() {
		root = NULL;
		size = 0;
	}
	~leaderBoard() {
		clear(root);
	}
	void insert(person* p) {
		if (!p) {
			cout << "No Player Found!" << endl;
			return;
		}
		root = insertHelper(root, p);
	}
	int getSize() {
		return size;
	}
	void remove(person* p) {
		if (!p)
			return;
		root = removeHelper(root, p);
	}
	void displayAscending() {
		cout << "<==(LEADER BOARD - Ascending)==>" << endl;
		printInorder(root);
	}

	void displayDescending() {
		cout << "<==(LEADER BOARD - Descending)==>" << endl;
		printInReverse(root);
	}
	void displayHighest() {
		if (!root)
			return;
		cout << "Top Player's Record:\n" << *findMax(root)->player << endl;
	}
	void displayLowest() {
		if (!root)
			return;
		cout << "Bottom Most Player's Record:\n" << *findMin(root)->player << endl;
	}
	vector<person*> Nearby_K_Opponents(int playerID, int k) {
		return K_nearby_Helper(playerID, k);
	}

	
};