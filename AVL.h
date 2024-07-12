#include "Node.h"

#include <iostream>
#include <ostream>
#include <queue>
#include <stack>

template <typename T>
class AVL
{
public:
	AVL(Node<T>* root = nullptr);
	~AVL();

	void insertR(const T& data);

	void eraseR(const T& data);

	bool findR(const T& data) const;
	bool findI(const T& data) const;
	T findMinR() const;
	T findMinI() const;
    T findMaxR() const;
    T findMaxI() const;

	void inorderR() const;
	void preorderR() const;
	void postorderR() const;

	void preorderI() const;
	void inorderI() const;
	void postorderI() const;
	void levelorder() const;

	int countOfNodesR() const;
    int countOfNodesI() const;
	int countOfLeavesR() const;
	int countOfLeavesI() const;

	int heightR() const;
	int heightI() const;

	int widthI() const;
	int widthR() const;

	void clearR();

    Node<T>* getPredecessor(T& val) const;
    Node<T>* getSuccessor(T& val) const;


private:
	Node<T>* insertHelper(Node<T>* ptr, const  T& data);

	Node<T>* eraseHelper(Node<T>* ptr, const T& data);

	Node<T>* findHelper(Node<T>* ptr, const T& data) const;
	Node<T>* findMinHelper(Node<T>* ptr) const;
	Node<T>* findMaxHelper(Node<T>* ptr) const;

	void inorderHelper(Node<T>* ptr) const;
	void preorderHelper(Node<T>* ptr) const;
	void postorderHelper(Node<T>* ptr) const;

	int countOfNodesHelper(Node<T>* ptr) const;
	int countOfLeavesHelper(Node<T>* ptr) const;

	int heightHelper(Node<T>* ptr) const;
	int widthHelper(Node<T>* ptr, int i) const;

	void clearHelper(Node<T>* ptr);

    int getBalanceFactor(Node<T>* ptr) const;

    Node<T>* rightRotate(Node<T>* ptr);
    Node<T>* leftRotate(Node<T>* ptr);
    Node<T>* balance(Node<T>* ptr);

private:
	Node<T>* m_root;
};


template <typename T>
AVL<T>::AVL(Node<T>* root)
{
    m_root = root;
}

template <typename T>
AVL<T>::~AVL()
{
    clearR();
}


template <typename T>
void AVL<T>::insertR(const T& data)
{
    m_root = insertHelper(m_root, data);
}

template <typename T>
Node<T>* AVL<T>::insertHelper(Node<T>* ptr, const T& data)
{
    if (ptr == nullptr) {
        ptr = new Node<T>(data);
        return ptr;
    }

    if (data > ptr->data) {
        ptr->right = insertHelper(ptr->right, data);
    } else if (data < ptr->data) {
        ptr->left = insertHelper(ptr->left, data);
    }
    
    return balance(ptr);
}


template <typename T>
void AVL<T>::eraseR(const T& data)
{
    m_root = eraseHelper(m_root, data);
}

template <typename T>
Node<T>* AVL<T>::eraseHelper(Node<T>* ptr, const T& data)
{
    if (ptr == nullptr) {
        return ptr;
    }

    if (ptr->left == nullptr) {
        Node<T>* tmp = ptr->right;
        delete ptr;
        return tmp;
    } else if (ptr->right == nullptr) {
        Node<T>* tmp = ptr->left;
        delete ptr;
        return tmp;
    } 
    Node<T>* temp = findMinHelper(ptr->right);
    ptr->data = temp->data;
    ptr->right = eraseHelper(ptr->right, temp->data);

    return balance(ptr);
}


template <typename T>
void AVL<T>::clearR()
{
    clearHelper(m_root);
    m_root = nullptr;
}

template <typename T>
void AVL<T>::clearHelper(Node<T>* ptr)
{
    if (ptr == nullptr) {
        return;
    }

    clearHelper(ptr->left);
    clearHelper(ptr->right);
    delete ptr;
    ptr = nullptr;
}


template <typename T>
bool AVL<T>::findI(const T& data) const
{
    if (m_root == nullptr) {
        return false;
    }
    

    Node<T>* ptr = m_root;
    while (ptr != nullptr) {
        if (data < ptr->data) {
            ptr = ptr->left;
        } else if (data > ptr->data) {
            ptr = ptr->right;
        } else {
            return true;
        }
    }

    return false;
}


template <typename T>
bool AVL<T>::findR(const T& data) const
{
    return findHelper(m_root, data) != nullptr;
}

template <typename T>
Node<T>* AVL<T>::findHelper(Node<T>* ptr, const T& data) const
{
    if (ptr == nullptr) {
        return nullptr;
    }

    if (data > ptr->data) {
        return findHelper(ptr->right , data);
    }
    if (data < ptr->data) {
        return findHelper(ptr->left, data);
    }

    return ptr;
}


template <typename T>
T AVL<T>::findMaxI() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }

    Node<T>* ptr = m_root;
    while (ptr->right != nullptr) {
        ptr = ptr->right;
    }

    return ptr->data;
}

template <typename T>
T AVL<T>::findMinI() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }

    Node<T>* ptr = m_root;
    while (ptr->left != nullptr) {
        ptr = ptr->left;
    }

    return ptr->data;
}

template <typename T>
T AVL<T>::findMaxR() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }
    return findMaxHelper(m_root)->data;
}

template <typename T>
Node<T>* AVL<T>::findMaxHelper(Node<T>* ptr) const
{
    if (ptr->right == nullptr) {
        return ptr;
    }

    return findMaxHelper(ptr->right);
}


template <typename T>
T AVL<T>::findMinR() const
{
    if (m_root == nullptr) {
        std::cout << "Root is nullptr" << std::endl;
        return T{};
    }

    return findMinHelper(m_root)->data;
}

template <typename T>
Node<T>* AVL<T>::findMinHelper(Node<T>* ptr) const
{
    if (ptr->left == nullptr) {
        return ptr;
    } 

    return findMinHelper(ptr->left);
}


template <typename T>
int AVL<T>::heightI() const
{
    std::queue<Node<T>*> q;
	q.push(m_root);

	int height = 0;

	while (!q.empty()) {
		const int size = q.size();
		for (int i = 0; i < size; i++) {
			Node<T>* ptr = q.front();
			q.pop();

			if (ptr->left != nullptr) {
				q.push(ptr->left);
			}

			if (ptr->right != nullptr) {
				q.push(ptr->right);
			}
		}
		++height;
	}
	return height;

}


template <typename T>
int AVL<T>::heightR() const
{
    return heightHelper(m_root);
}

template <typename T>
int AVL<T>::heightHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }
    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }
    
    return std::max(heightHelper(ptr->left), heightHelper(ptr->right)) + 1;
}


template <typename T>
void AVL<T>::inorderR() const
{
    inorderHelper(m_root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::inorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }

    inorderHelper(ptr->left);
    std::cout << ptr->data << " ";
    inorderHelper(ptr->right);
}


template <typename T>
void AVL<T>::preorderR() const
{
    preorderHelper(m_root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::preorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }

    std::cout << ptr->data << " ";
    preorderHelper(ptr->left);
    preorderHelper(ptr->right);
}


template <typename T>
void AVL<T>::postorderR() const
{
    preorderHelper(m_root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::postorderHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return;
    }

    postorderHelper(ptr->left);
    postorderHelper(ptr->right);
    std::cout << ptr->data << " ";
}


template <typename T>
void AVL<T>::inorderI() const
{
    std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;

	while (true) {
		while (ptr != nullptr) {
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) { 
			return;
        }

		ptr = stk.top();
		stk.pop();
		std::cout << ptr->data << ' ';

		ptr = ptr->right;
	}
}


template <typename T>
void AVL<T>::preorderI() const
{
    std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;

	while (true) {
		while (ptr != nullptr) {
			std::cout << ptr->data << " ";
			
			if (ptr->right) {
				stk.push(ptr->right);
			}

			ptr = ptr->left;
		}

		if (stk.empty()) {
			return;
		}
		
		ptr = stk.top();
		stk.pop();
	}
}


template <typename T>
void AVL<T>::postorderI() const
{
	std::stack<Node<T>*> stk;
	Node<T>* ptr = m_root;
	
	while (true) {
		while (ptr != nullptr) {
			if (ptr->right) {
				stk.push(ptr->right);
			}
			stk.push(ptr);
			ptr = ptr->left;
		}

		if (stk.empty()) {
			return;
		}

		ptr = stk.top();
		stk.pop();
		if (ptr->right && !stk.empty() && stk.top() == ptr->right) {
			stk.pop();
			stk.push(ptr);
			ptr = ptr->right;
		} else {
			std::cout << ptr->data << ' '; 
			ptr = nullptr;
		}
	}
}


template <typename T>
void AVL<T>::levelorder() const
{
    if (m_root != nullptr) {
        std::queue<Node<T>*> q{};
        q.push(m_root);
        
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node<T>* ptr = q.front();
                q.pop();
                if (ptr->left != nullptr) {
                    q.push(ptr->left);
                }
                if (ptr->right != nullptr) {
                    q.push(ptr->right);
                }
                std::cout << ptr->data << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


template <typename T>
int AVL<T>::countOfNodesI() const
{
    if (m_root != nullptr) {
        std::queue<Node<T>*> q{};
        q.push(m_root);
        int count = 0;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node<T>* ptr = q.front();
                q.pop();
                if (ptr->left != nullptr) {
                    q.push(ptr->left);
                }
                if (ptr->right != nullptr) {
                    q.push(ptr->right);
                }
                ++count;
            }
        }
        return count;

    }

    return 0;
}


template <typename T>
int AVL<T>::countOfNodesR() const
{
    return countOfNodesHelper(m_root);
}

template <typename T>
int AVL<T>::countOfNodesHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }

    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }

    return countOfNodesHelper(ptr->left) + countOfNodesHelper(ptr->right) + 1;
}


template <typename T>
int AVL<T>::countOfLeavesI() const
{
    if (m_root != nullptr) {
        std::queue<Node<T>*> q{};
        q.push(m_root);
        int count = 0;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; ++i) {
                Node<T>* ptr = q.front();
                q.pop();
                if (ptr->left != nullptr) {
                    q.push(ptr->left);
                }
                if (ptr->right != nullptr) {
                    q.push(ptr->right);
                }
                if (ptr->left == nullptr && ptr->right == nullptr) {
                    ++count;
                }
            }
        }
        return count;
    }

    return 0;
}


template <typename T>
int AVL<T>::countOfLeavesR() const
{
    return countOfLeavesHelper(m_root);
}

template <typename T>
int AVL<T>::countOfLeavesHelper(Node<T>* ptr) const
{
    if (ptr == nullptr) {
        return 0;
    }

    if (ptr->left == nullptr && ptr->right == nullptr) {
        return 1;
    }

    return countOfLeavesHelper(ptr->left) + countOfLeavesHelper(ptr->right);
}


template <typename T>
int AVL<T>::widthR() const
{
    int width = 0;
    int height = heightR();

    for (int i = 0; i <= height; ++i) {
        int currentWidth = widthHelper(m_root, i);
        if (currentWidth > width) {
            width = currentWidth;
        }
    }
    return width;
}

template <typename T>
int AVL<T>::widthHelper(Node<T>* ptr, int level) const
{
    if (ptr == nullptr) {
        return 0;
    }

    if (level == 0) {
        return 1;
    }

    return widthHelper(ptr->left, level - 1) + widthHelper(ptr->right, level - 1);
}


template <typename T>
int AVL<T>::widthI() const
{
	std::queue<Node<T>*> q;
	q.push(m_root);
	int width = 0;

	while (!q.empty()) {
		const int size = q.size();
		width = std::max(size, width); 
		for (int i = 0; i < size; i++) {
			Node<T>* ptr = q.front();
			q.pop();

			if (ptr->left) {
				q.push(ptr->left);
			}

			if (ptr->right) {
				q.push(ptr->right);
			}
		}
	}
	return width;
}


template <typename T>
int AVL<T>::getBalanceFactor(Node<T>* ptr) const
{
    return heightHelper(ptr->left) - heightHelper(ptr->right);
}


template <typename T>
Node<T>* AVL<T>::balance(Node<T>* ptr) 
{
    int bf = getBalanceFactor(ptr);
    
    if (bf > 1 && ptr->left != nullptr && getBalanceFactor(ptr->left) >= 0) {
        return rightRotate(ptr);
    } 

    if (bf > 1 && ptr->left != nullptr && getBalanceFactor(ptr->left) < 0) {
        ptr->left = leftRotate(ptr->left);
        return rightRotate(ptr);
    }

    if (bf < -1 && ptr->right != nullptr && getBalanceFactor(ptr->left) <= 0) {
        return leftRotate(ptr);
    }

    if (bf < -1 && ptr->right != nullptr && getBalanceFactor(ptr->left) > 0) {
        ptr->right = rightRotate(ptr->right);
        return leftRotate(ptr);
    }

    return ptr;
}

template <typename T>
Node<T>* AVL<T>::rightRotate(Node<T>* ptr)
{
    Node<T>* y = ptr->left;
    Node<T>* T3 = y->right;
    y->right = ptr;
    ptr->left = T3;

    return y;
}

template <typename T>
Node<T>* AVL<T>::leftRotate(Node<T>* ptr)
{
    Node<T>* y = ptr->right;
    Node<T>* T2 = y->left;
    y->left = ptr;
    ptr->right = T2;
    
    return y;
}


template <typename T>
Node<T>* AVL<T>::getPredecessor(T& val) const
{
    Node<T>* ptr = m_root;
    while (ptr != nullptr) {
        if (val < ptr->data) {
            ptr = ptr->left;
        } else if (val > ptr->data) {
            ptr = ptr->right;
        } else {
            break;
        }
    }

    if (ptr != nullptr) {
        return findMaxHelper(ptr->left);
    }
    return ptr;
}

template <typename T>
Node<T>* AVL<T>::getSuccessor(T& val) const
{
    Node<T>* ptr = m_root;
    while (ptr != nullptr) {
        if (val < ptr->data) {
            ptr = ptr->left;
        } else if (val > ptr->data) {
            ptr = ptr->right;
        } else {
            break;
        }
    }
    
    if (ptr != nullptr) {
        return findMinHelper(ptr->right);
    }
    return ptr;
}
