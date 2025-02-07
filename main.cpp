/**
 * @author gh Corgice @IceSandwich
 * @date Jun 2023
 * @lincense MIT
 */

#include <iostream>
#include <functional>
#include <thread>
using namespace std;

template<int id>
struct Node {
    static bool execute() {
        if (id >= 3) {
            cout << "Node " << id << ", this is abort node which will ban the following nodes." << endl;
            return false;
        } else {
            cout << "Node " << id << endl;
            return true;
        }
    }
};

template<typename... Tail>
struct Sequential {
    static bool execute() {
        return (... && (std::cout << "Enter node: " << std::endl, Tail::execute()));
    }
};

template <typename... Tail>
struct Selector {
    static bool execute() {
        return !(... && (std::cout << "Enter node: " << std::endl, !Tail::execute()));
    }
};


template<typename node_, int id_>
struct NodeWrapper {
    using node = node_;
    static constexpr int id = id_;
};

template<typename node1_, typename node2_>
struct Link {
    using node1 = node1_;
    using node2 = node2_;
};

// �ڵ�����
template<int id>
struct MyNode {
    static void execute() {
        cout << "Node " << id << endl;
    }
};

// �ڵ�ͼ��ÿ���ڵ㶼��һ��ΨһID��ʶ
using Node1 = NodeWrapper<MyNode<1>, 1>;
using Node2 = NodeWrapper<MyNode<2>, 2>;
using Node3 = NodeWrapper<MyNode<3>, 3>;
using Node4 = NodeWrapper<MyNode<4>, 4>;
using Node5 = NodeWrapper<MyNode<5>, 5>;

// ִ�з���: �ݹ�ִ�нڵ�֮������ֹʱ���л���
template<typename link>
struct ExecuteHelper {
    static void execute() {
        using node_left = typename link::node1;
        using node_right = typename link::node2;
        node_left::node::execute();
        ExecuteHelper<node_right>::execute();
    }
};

template<typename node>
struct ExecuteHelper<NodeWrapper<node, 5>> { // �ݹ���ֹ����
    static void execute() {}
};

int main() {
    // ���нڵ�ᰴ˳��ִ�����нڵ㣬ֱ������ִ��ʧ�ܵ�
    using MyTree = Sequential<Node<1>, Node<2>, Node<3>, Node<4>, Node<5>>;
    MyTree::execute();

    std::cout << "====================================" << std::endl;

    // ѡ��ڵ�ᰴ˳��ִ�����нڵ㣬ֱ������ִ�гɹ���
    // ע��ڵ����Ƕ��ʹ��
    using MyTree2 = Selector<Node<3>, Sequential<Node<1>, Node<2>>, Node<1>, Node<2>, Node<3>>;
    MyTree2::execute();

    std::cout << "====================================" << std::endl;

    // ��ͼ�ķ�ʽִ�нڵ㣬����Ҫ���ͼ�Ľ���
    ExecuteHelper< Link<Node1, Link<Node2, Link<Node3, Link<Node4, Node5>>>> >::execute();
	return 0;
}
