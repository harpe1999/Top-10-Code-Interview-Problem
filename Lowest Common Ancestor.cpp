#include<memory>
#include<iterator>
#include<iostream>
template<typename T>
struct node
{
	node() :parent(0), first_child(0), last_child(0),
	prev_sibling(0), next_sibling(0){}
	node(const T& val) :parent(0), first_child(0), last_child(0),
		prev_sibling(0), next_sibling(0), data(val){}
	node<T> *parent;
	node<T> *first_child, *last_child;
	node<T> *prev_sibling, *next_sibling;
	T data;
};

template <typename T, typename Allocator=std::allocator<node<T> > >
struct tree
{
	typedef node<T> tree_node;
	typedef T value_type;
	tree_node *head, *feet;
private:
	Allocator alloc_;
public:
	tree()
	{
		head = alloc_.allocate(1, 0);
		feet = alloc_.allocate(1, 0);
		alloc_.construct(head, node<T>());
		alloc_.construct(feet, node<T>());
		head->parent, head->first_child = 0;
		head->last_child, head->prev_sibling = 0;
		head->next_sibling = feet;
		feet->parent, feet->first_child = 0;
		feet->last_child, feet->next_sibling = 0;
		feet->prev_sibling = head;
	}

	struct iterator
	{
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		tree_node *node;
		iterator() :node(0){}
		iterator(tree_node*tn) :node(tn){}
		T& operator*()const
		{
			return node->data;
		}
		T* operator->()const
		{
			return &(node->data);
		}
		bool operator==(const iterator& o)const
		{
			if (o.node == this->node)return true;
			else return false;
		}
		bool operator!=(const iterator& o)const
		{
			if (o.node != this->node)return true;
			else return false;
		}

	};

	iterator begin() const
	{
		return iterator(head->next_sibling);
	}
	iterator end() const
	{
		return iterator(feet);
	}
	template<typename iter>
	static iter parent(iter p)
	{
		return iter(p.node->parent);
	}
	template<typename iter>
	iter append(iter p, const T& x)
	{
		tree_node* tmp = alloc_.allocate(1, 0);
		alloc_.construct(tmp, x);
		tmp->first_child, tmp->last_child = 0;
		tmp->parent = p.node;
		if (p.node->last_child != 0)
		{
			p.node->last_child->next_sibling = tmp;
		}
		else
		{
			p.node->first_child = tmp;
		}
		tmp->prev_sibling = p.node->last_child;
		p.node->last_child = tmp;
		tmp->next_sibling = 0;
		return tmp;
	}

	static int level(const iterator& it)
	{
		tree_node* pos = it.node;
		int l = 0;
		while (pos->parent != 0)
		{
			pos = pos->parent;
			++l;
		}
		return l;
	}

	template<typename iter>
	iter insert(iter p, const T& x)
	{
		if (p.node == 0)
		{
			p.node = feet;
		}
		tree_node* tmp = alloc_.allocate(1, 0);
		alloc_.construct(tmp, x);
		tmp->first_child, tmp->last_child = 0;
		tmp->parent = p.node->parent;
		tmp->next_sibling = p.node;
		tmp->prev_sibling = p.node->prev_sibling;
		if (tmp->prev_sibling == 0)
		{
			if (tmp->parent)
				tmp->parent->first_child = tmp;
		}
		else
		{
			tmp->prev_sibling->next_sibling = tmp;
		}
		return tmp;
	}

};


template<typename T,typename Iter=tree<T>::iterator>
Iter lca(const tree<T> & tree,
	Iter u,
	Iter v
)
{
	std::stack<typename tree<T>::iterator> s1, s2;
	typename tree<T>::iterator lca;
	do
	{
		sl.push(u);
		if (u != tree.begin())
			u = tree.begin();
	} while (u != tree.begin());
	
	sl.push(tree.begin());

	do
	{
		s2.push(v);
		if (v != tree.begin())
			v = tree.parent(v);
	} while (v != tree.begin());

	while (!s1.empty && !s2.empty() && (s1.top() == s2.top()))
	{
		lca = s1.top();
		s1.pop();
		s2.pop();
	}
	return lca;
}
int main()
{
	tree<std::string> st;
	tree<std::string>::iterator itra
		= st.insert(st.begin(), "a");
	tree<std::string>::iterator itrb
		= st.append(itra, "b");
	tree<std::string>::iterator itrc
		= st.append(itra, "c");

	tree<std::string>::iterator itrd, itre;
	itrd = st.append(itrb, "d");
	itre = st.append(itrb, "e");
	st.append(itre, "h");

	tree<std::string>::iterator itri
		= st.append(itre, "i");
	tree<std::string>::iterator itrm
		= st.append(itri, "m");
	tree<std::string>::iterator itrn
		= st.append(itri, "n");
	tree<std::string>::iterator itro
		= st.append(itri, "o");

	tree<std::string>::iterator itrf
		= st.append(itrd, "f");
	tree<std::string>::iterator itrg
		= st.append(itrd, "g");
	tree<std::string>::iterator itrj
		= st.append(itrf, "j");
	tree<std::string>::iterator itrk
		= st.append(itrf, "k");
	tree<std::string>::iterator itrl
		= st.append(itrf, "l");


	std::cout << "levels of nodes \n:"
		<< "\na: " << st.level(itra)
		<< "\nb: " << st.level(itrb)
		<< "\nd: " << st.level(itrd)
		<< "\ne: " << st.level(itre)
		<< "\ni: " << st.level(itri)
		<< "\nf: " << st.level(itrf)
		<< "\n" << std::endl;

	tree<std::string>::iterator pi, pe, pb;
	pi = tree<std::string>::parent(itri);
	pe = tree<std::string>::parent(pi);
	pb = tree<std::string>::parent(pe);

	//std::cout << "lca of b and c : "
	//	<< *lca(st, itrb, itrc) << std::endl;
	//std::cout << "lca of d and e : "
	//	<< *lca(st, itrd, itre) << std::endl;
	//std::cout << "lca of f and e : "
	//	<< *lca(st, itrf, itre) << std::endl;
	//std::cout << "lca of f and i : "
	//	<< *lca(st, itrf, itri) << std::endl;
	//std::cout << "lca of f and g : "
	//	<< *lca(st, itrf, itrg) << std::endl;
	//std::cout << "lca of j and l : "
	//	<< *lca(st, itrj, itrl) << std::endl;
	//std::cout << "lca of l and o: "
	//	<< *lca(st, itrl, itro) << std::endl;
	//std::cout << "lca of b and o : "
	//	<< *lca(st, itrb, itro) << std::endl;
	//std::cout << "lca of a and a : "
	//	<< *lca(st, itra, itra) << std::endl;
	//std::cout << "lca of j and c : "
	//	<< *lca(st, itrj, itrc) << std::endl;
	//std::cout << "lca of d and c : "
	//	<< *lca(st, itrd, itrc) << std::endl;

	return 0;
}
