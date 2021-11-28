#include <bits/stdc++.h>
using namespace std;
typedef long long int lli;
lli freq_array[256];

typedef struct freq_tree
{
    char ch;
    lli freq;
    bool leaf_node;
    struct freq_tree *leftChild;
    struct freq_tree *rightChild;
} freq_tree_node;

struct compare // defining the comparator for the minheap
{
    bool operator()(freq_tree_node *a, freq_tree_node *b)
    {
        return a->freq > b->freq;
    }
};

freq_tree_node *create_node(char ch, int freq, bool leaf_flag)
{
    freq_tree_node *node = (freq_tree_node *)malloc(sizeof(freq_tree_node));
    node->ch = ch;
    node->freq = freq;
    node->leaf_node = leaf_flag;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}
priority_queue<freq_tree_node *, vector<freq_tree_node *>, compare> minHeap;

void encode(freq_tree_node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
    {
        return;
    }

    // found a leaf node
    if (root->leaf_node)
    {
        huffmanCode[root->ch] = (str != "") ? str : "1";
    }

    encode(root->leftChild, str + "0", huffmanCode);
    encode(root->rightChild, str + "1", huffmanCode);
}

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        cout << "Too Less Arguments" << endl;
        return 1;
        break;
    case 2:
        break;
    default:
        cout << "Too Many Arguments" << endl;
        return 1;
        break;
    }

    FILE *fd = fopen((char *)argv[1], "r");
    if (fd == NULL)
    {
        cout << "File Not Found" << endl;
        return 1;
    }
    for (int i = 0; i < 256; i++)
    {
        freq_array[i] = 0;
    }
    char r = fgetc(fd);
    while (r != EOF)
    {
        freq_array[r]++;
        r = fgetc(fd);
    };

    for (int i = 0; i < 256; i++)
    {
        if (freq_array[i] != 0)
        {
            freq_tree_node *temp = create_node((char)i, freq_array[i], true);
            minHeap.push(temp);
        }
    }

    while (minHeap.size() > 1)
    {
        freq_tree_node *left = minHeap.top();
        minHeap.pop();
        freq_tree_node *right = minHeap.top();
        minHeap.pop();
        freq_tree_node *temp = create_node('\0', left->freq + right->freq, false);
        temp->leftChild = left;
        temp->rightChild = right;
        minHeap.push(temp);
    }

    unordered_map<char, string> huffmanCode;
    freq_tree_node *root = minHeap.top();
    encode(root, "", huffmanCode);

    // got the code tree up now iterate over the file again and encode it

    fclose(fd);

    FILE *opt = fopen("output.txt", "w");
    if (opt == NULL)
    {
        cout << "ERROR in creating output file" << endl;
        return 1;
    }

    fd = fopen((char *)argv[1], "r");
    if (fd == NULL)
    {
        cout << "Input File Not Found" << endl;
        return 1;
    }

    r = fgetc(fd);
    while (r != EOF)
    {
        fprintf(opt, "%s", huffmanCode[r].c_str());
        r = fgetc(fd);
    }

    fclose(fd);
    fclose(opt);

    return 0;
}