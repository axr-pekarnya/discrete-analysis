#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>

const char DEFAULT_COLOUR = 1;

class TItem
{
    public:
        TItem(): key(""), value(0) {}

        std::string& GetKey() {
            return key;
        }

        uint64_t GetValue() const {
            return value;
        }

        void SetKey(std::string& keyInput){
            this->key = keyInput;
        }

        void SetValue(uint64_t valueInput){
            this->value = valueInput;
        }

        friend std::istream& operator>>(std::istream& fin, TItem& elem)
        {
            fin >> elem.key >> elem.value;
            return fin;
        }
       
        friend std::ostream& operator<<(std::ostream& fout, const TItem& elem)
        {
            fout << elem.key << ' ' << elem.value << '\n';
            return fout;
        }

    private:
        std::string key;
        uint64_t value;
};

class TNode 
{
    public:
        TNode* parent;
        TNode* left;
        TNode* right;
        bool colour;

        TNode(TNode* parentInput, TNode* leftInput, TNode* rightInput, bool colourInput, TItem& dataInput)
        {
            this->parent = parentInput;
            this->left = leftInput;
            this->right = rightInput;
            this->colour = colourInput;
            this->data = dataInput;
        }

        TItem GetData() const {
            return this->data;
        }

        void SetData(const TItem& elem) {
            this->data = elem;
        }

    private:
        TItem data;
};

class TRedBlackTree
{
    protected:

        int Compare(const std::string& str1, const std::string& str2)
        {
            int len = std::min(str1.length(), str2.length());
            
            for(int i = 0; i < len; ++i)
            {
                if (std::tolower(str1[i]) > std::tolower(str2[i])){
                    return 1;
                } 
                else if (std::tolower(str1[i]) < std::tolower(str2[i])){
                    return -1;
                }
            }

            if (str1.length() > str2.length()){
                return 1;
            } 
            else if (str1.length() < str2.length()){
                return -1;
            } 
            else {
                return 0;
            }
        }



        TNode* Left(TNode* node)
        {
            if (node->left){
                return Left(node->left);
            }

            return node;
        }

        TNode* Right(TNode* node)
        {
            if (node->right){
                return Left(node->right);
            }
            
            return node;
        }

        

        TNode* LeftRotation(TNode* node)
        {
            TNode* parent = node->parent;
            TNode* cur = node;

            bool curColour = cur->colour;
            
            cur->colour = parent->colour;
            parent->colour = curColour;
            parent->right = cur->left;
            
            if (cur->left){
                cur->left->parent = parent;
            }

            cur->left = parent;
            cur->parent = parent->parent;
            
            if (parent->parent && parent->parent->left == parent) {
                parent->parent->left = cur;
            } 
            else if (parent->parent){
                parent->parent->right = cur;
            }

            parent->parent = cur;

            if (cur->parent == NULL){
                root = parent;
            }
            
            return root;
        }

        TNode* RightRotation(TNode* node)
        {
            TNode* parent = node->parent;
            TNode* cur = node;

            bool curColour = cur->colour;

            cur->colour = parent->colour;
            parent->colour = curColour;
            parent->left = cur->right;
            
            if (cur->right){
                cur->right->parent = parent;
            }
            
            cur->right = parent;
            cur->parent = parent->parent;
            
            if (parent->parent && parent->parent->left == parent) {
                parent->parent->left = cur;
            }
            else if (parent->parent){
                parent->parent->right = cur;
            }
            
            parent->parent = cur;
            
            if (cur->parent == NULL){
                root = cur;
            }
            
            return root;
        }



    public:

        TNode* root = NULL;
        TRedBlackTree() = default;

        TNode* Insert(TNode* node, TItem& data)
        {
            if (root == NULL)
            {
                root = new TNode(NULL, NULL, NULL, false, data);
                std::cout << "OK" << std::endl;
            
                return root;
            }

            int next = Compare(data.GetKey(), node->GetData().GetKey());
            
            if (!next)
            {
                std::cout << "Exist" << std::endl;

                return root;
            } 
            else if (next == 1)
            {
                if (node->right == NULL)
                {
                    node->right = new TNode(node, NULL, NULL, true, data);
                    std::cout << "OK" << std::endl;
                
                    InsertBalance(node->right);
                    return root;
                } 
                else {
                    Insert(node->right, data);
                }
            } 
            else
            {
                if (node->left == NULL)
                {
                    node->left = new TNode(node, NULL, NULL, true, data);
                    std::cout << "OK" << std::endl;
                
                    InsertBalance(node->left);
                    return root;
                } 
                else {
                    Insert(node->left, data);
                }
            }

            return root;
        }



        TNode* Erase(TNode* node)
        {
            if (!node->parent && !node->left && !node->right)
            {
                delete node;
                std::cout << "OK" << std::endl;
                
                this->root = NULL;
                return root;
            }

            TNode *replacement;
            
            if (node->colour)
            {
                if (!node->right && !node->left) 
                {
                    if (node->parent) 
                    {
                        if (node->parent->left == node) {
                            node->parent->left = NULL;
                        }
                        else {
                            node->parent->right = NULL;
                        }
                    }

                    delete node;
                    std::cout << "OK" << std::endl;
                
                    return root;
                } 
                else if (node->right) 
                {
                    replacement = Left(node->right);
                    node->SetData(replacement->GetData());
                
                    return Erase(replacement);
                } 
                else if (node->left) 
                {
                    replacement = Right(node->left);
                    node->SetData(replacement->GetData());
                
                    return Erase(replacement);
                }
            } 
            else
            {
                if (node->left && node->left->colour && !node->right)
                {
                    if (node->parent) 
                    {
                        if (node->parent->left == node) {
                            node->parent->left = node->left;
                        }
                        else {
                            node->parent->right = node->left;
                        }
                    }
                    else {
                        root = node->left;
                    }
                    
                    node->left->colour = false;
                    node->left->parent = node->parent;
                    
                    delete node;
                    
                    std::cout << "OK" << std::endl;
                    return root;
                } 
                else if (node->right && node->right->colour && !node->left)
                {
                    if (node->parent) 
                    {
                        if (node->parent->left == node) {
                            node->parent->left = node->right;
                        }
                        else {
                            node->parent->right = node->right;
                        }
                    } 
                    else {
                        root = node->right;
                    }
                
                    node->right->colour = false;
                    node->right->parent = node->parent;
                
                    delete node;
                
                    std::cout << "OK" << std::endl;
                    return root;
                }
                else if (!node->right && !node->left)
                {
                    EraseBalance(node);
                 
                    if (node->parent) 
                    {
                        if (node->parent->left == node) {
                            node->parent->left = NULL;
                        }
                        else {
                            node->parent->right = NULL;
                        }
                    }
                    
                    delete node;
                    
                    std::cout << "OK" << std::endl;
                    return root;
                }
                else
                {
                    replacement = node->right ? Left(node->right) : Right(node->left);
                    node->SetData(replacement->GetData());

                    Erase(replacement);
                }
            }

            return root;
        }



        TNode* Find(TNode* node, const std::string& key)
        {
            if (node == NULL) {
                return NULL;
            }

            int next = Compare(key, node->GetData().GetKey());
            
            if(!next){
                return node;
            }
            else if (next == 1){
                return Find(node->right, key);
            } 
            else {
                return Find(node->left, key);
            }
        }
       


        TNode* EraseBalance(TNode* node)
        {
            if (!node->parent){
                return root;
            }
            
            TNode* brother = node->parent->right;
            bool side = false;
            
            if (node->parent->right == node)
            {
                side = true;
                brother = node->parent->left;
            }
        
            if (brother == NULL){
                return EraseBalance(node->parent);
            }
            if (brother->colour) 
            {
                side ? RightRotation(brother) : LeftRotation(brother);
                return EraseBalance(node);
            }
            else
            {
                if ((!brother->left || !brother->left->colour) && (!brother->right || !brother->right->colour))
                {
                    brother->colour = true;
                
                    if (brother->parent->colour)
                    {
                        brother->parent->colour = false;
                        return root;
                    } 
                    else {
                        return EraseBalance(brother->parent);
                    }

                }
                if (side)
                {
                    if ((!brother->left || !brother->left->colour) && brother->right->colour)
                    {
                        LeftRotation(brother->right);
                        return EraseBalance(node);
                    }
                    
                    brother->left->colour = false;
                    return RightRotation(brother);
                } 
                else
                {
                    if ((!brother->right || !brother->right->colour) && brother->left->colour)
                    {
                        RightRotation(brother->left);
                        return EraseBalance(node);
                    }
                    
                    brother->right->colour = false;
                    return LeftRotation(brother);
                }
            }
        }



        TNode* InsertBalance(TNode* node)
        {
            if (!node->parent || !node->parent->colour) {
                return root;
            }
            
            if (node->parent->parent->left == node->parent)
            {
                if (node->parent->parent->right == NULL || !node->parent->parent->right->colour) 
                {
                    if (node->parent->right == node)
                    {
                        LeftRotation(node);
                        RightRotation(node);
                   
                        return root;
                    } 
                    else
                    {
                        RightRotation(node->parent);
                        return root;
                    }
                }
                else if (node->parent->parent->right->colour) 
                {
                    node->parent->colour = false;
                    node->parent->parent->right->colour = false;
                
                    if (node->parent->parent->parent != NULL) {
                        node->parent->parent->colour = true;
                    }

                    if (node->parent->parent->parent && node->parent->parent->parent->colour){
                        return InsertBalance(node->parent->parent);
                    }
                }
            } 
            else 
            {
                if (node->parent->parent->left == NULL || !node->parent->parent->left->colour)
                {
                    if (node->parent->left == node)
                    {
                        RightRotation(node);
                        LeftRotation(node);
                    
                        return root;
                    } 
                    else 
                    {
                        LeftRotation(node->parent);
                        return root;
                    }
                }
                else if (node->parent->parent->left->colour) 
                {
                    node->parent->colour = false;
                    node->parent->parent->left->colour = false;
                    
                    if (node->parent->parent->parent != NULL) {
                        node->parent->parent->colour = true;
                    }
                    
                    if(node->parent->parent->parent && node->parent->parent->parent->colour){
                        return InsertBalance(node->parent->parent);
                    }
                }
            }

            return root;
        }



        static void Clear(TNode *node)
        {
            if (!node){
                return;
            }

            Clear(node->left);
            Clear(node->right);
            
            delete node;
        }
};



class TFormatter
{
    friend class TFileManager;

    private:
        char colour;
        uint64_t value;
        std::string key;

        TFormatter()
        {
            this->colour = DEFAULT_COLOUR;
            this->value = 0;
        }

        TFormatter(char colourInput, uint64_t valueInput, std::string& keyInput)
        {
            this->colour = colourInput;
            this->value = valueInput;
            this->key = keyInput;
        }

        friend std::istream& operator>>(std::istream& fin, TFormatter& elem)
        {
            fin >> elem.colour >> elem.value >> elem.key;
            return fin;
        }

        friend std::ostream& operator<<(std::ostream& fout, const TFormatter& elem)
        {
            fout << elem.colour << elem.value << elem.key << ' ';
            return fout;
        }
};



class TFileManager
{
    friend TFormatter;

    public:
        TFileManager() = default;
        
        static void Save(TNode* node, std::ofstream &fout)
        {
            if (!fout.is_open()){
                return;
            }

            if (!node)
            {
                TFormatter itemOutput;
                fout << itemOutput;
            } 
            else
            {
                TFormatter itemOutput(node->colour + '0', node->GetData().GetValue(), node->GetData().GetKey());
                fout << itemOutput;

                Save(node->left, fout);
                Save(node->right, fout);
            }
        }

        static TNode* Load(TNode *node, std::ifstream &fin)
        {
            TFormatter itemInput;
            TItem data;

            if (!fin.is_open()){
                return node;
            }

            fin >> itemInput;
        
            if (itemInput.colour != DEFAULT_COLOUR)
            {
                data.SetKey(itemInput.key);
                data.SetValue(itemInput.value);
             
                if (itemInput.colour == '0'){
                    node = new TNode(NULL, NULL, NULL, false, data);
                } 
                else {
                    node = new TNode(NULL, NULL, NULL, true, data);
                }
            
                node->left = Load(node->left, fin);
            
                if (node->left){
                    node->left->parent = node;
                }

                node->right = Load(node->right, fin);
            
                if (node->right){
                    node->right->parent = node;
                }

                return node;
            }

            return NULL;
        }
};



int main()
{
    std::ofstream fout;
    std::ifstream fin;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::string strInput;
    std::string key;
    
    TRedBlackTree *tree = new TRedBlackTree();
    TFileManager* fileManager = new TFileManager();
    TItem data;
    
    while (std::cin >> strInput) 
    {
        if (!strInput.compare("+")) 
        {
            std::cin >> data;
            tree->Insert(tree->root, data);
        }
        else if (!strInput.compare("-")) 
        {
            std::cin >> key;
        
            TNode *need_to_delete = tree->Find(tree->root, key);
        
            if (need_to_delete == NULL) {
                std::cout << "NoSuchWord" << std::endl;
            }
            else {
                tree->Erase(need_to_delete);
            }
        }
        else if (!strInput.compare("!")) 
        {
            std::cin >> strInput;

            if (!strInput.compare("Save")) 
            {
                std::cin >> strInput;

                fout.open(strInput,  std::ios::out | std::ios::binary | std::ios::trunc);

                fileManager->Save(tree->root, fout);
                
                fout.close();

                std::cout << "OK" << std::endl;
            }
            else if (!strInput.compare("Load")) 
            {
                std::cin >> strInput;
                
                fin.open(strInput, std::ios::in | std::ios::binary);
                
                tree->Clear(tree->root);
                tree->root = fileManager->Load(tree->root, fin);
                
                fin.close();

                std::cout << "OK" << std::endl;
            }
        }
        else if (!strInput.compare("`")) 
        {
            tree->Clear(tree->root);

            delete tree;
            return 0;
        }
        else 
        {
            key = strInput;
            TNode *temp = tree->Find(tree->root, key);
        
            if (temp == NULL){
                std::cout << "NoSuchWord" << std::endl;
            }
            else { 
                std::cout << "OK: " << temp->GetData().GetValue() << std::endl;
            }
        }
    }

    delete tree;
    return 0;
}
