#include "Graph.h"
#include "Simple_window.h"

class treenode
{
public:
	treenode * left;
	treenode *right;
	Point p;
	string str;

	treenode(string s, int xx = 0, int yy = 0)
	{
		p.x = xx;
		p.y = yy;
		str = s;
	}
};

void append(char *str , char ch)
{
	int i = 0;
	while (str[i] != '\0')
		++i;
	str[i] = ch;
	str[i + 1] = '\0';
}

void creattree(treenode *root, int n)
{
	if (n > 0)
	{
		treenode *p1, *p2;
		p1 = new treenode(root->str, root->p.x - 4 * pow(2, n), root->p.y + 4 * pow(2, n));
		p2 = new treenode(root->str, root->p.x + 4 * pow(2, n), root->p.y + 4 * pow(2, n));
		p1->str += 'l';
		p2->str += 'r';
		root->left = p1;
		root->right = p2;
		creattree(p1, n - 1);
		creattree(p2, n - 1);
	}
	else
		return;
}

void preorder(treenode *root, int n)
{
	if (n > 0)
	{
		if (n > 1)
		{
			Text t(root->p, root->str);
			t.set_color(Color::black);
			t.set_font_size(15);
			t.draw();
			Line l1(root->p, root->left->p), l2(root->p, root->right->p);
			l1.set_color(Color::black);
			l2.set_color(Color::black);
			l1.draw();
			l2.draw();
			preorder(root->left, n - 1);
			preorder(root->right, n - 1);
		}
		else
		{
			Text t(root->p, root->str);
			t.set_color(Color::black);
			t.set_font_size(15);
			t.draw();
		}
	}
	else
		return;
}

class Binary_tree : public Shape
{
public:
	treenode * root;
	int n;

	Binary_tree(Point p, int nn)
	{
		n = nn;
		root = new treenode("\0" ,p.x, p.y);
		creattree(root, n);
	}
	virtual void draw_lines() const
	{
		preorder(root, n);
	}
};

int main()
{
	Simple_window win(Point(100, 100), 800, 800, "canvas");

	Point p(300, 300);
	Binary_tree b(p, 5);
	win.attach(b);

	win.wait_for_button();
}