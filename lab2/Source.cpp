#include "ISortedSequence.h"
#include "BackpackItems.h"
#include "NTree.h"
#include "ArraySequence.h"
#include <vector>
#include "crow_all.h"
#include <random>
#include <string>
#include <time.h>
#include <tuple>
#include <vector>
#include "BinaryTree.h"
#include "BinSearch.h"
#include "BTree.h"
#include "Hystogram.h"

// "C:\Program Files (x86)\Google\Chrome\Application\chrome.exe" --disable - web - security  --user - data - dir = ~/ chromeTemp


#define crow_json crow::json::wvalue

using namespace std;

ArraySequence<Item>* RandomItems(int size)
{
    ArraySequence<Item>* seq = new ArraySequence<Item>;
    for (int i = 0; i < size; i++)
    {
        double w = rand() % 200 + 1;
        double c = rand() % 1000 + 1;
        Item item(w, c);
        seq->Append(item);
    }
    return seq;
}

std::vector<std::string> StringItems(Sequence<Item>* seq)
{
    std::vector<std::string> res;
    for (int i = 0; i < seq->GetLenght(); i++)
    {
        std::string tmp = "";
        tmp = "Item " + std::to_string(i+1) + ": weight - " + std::to_string(seq->Get(i).GetWeight()) +
            " , cost - " + std::to_string(seq->Get(i).GetCost()) + " \n";
        res.push_back(tmp);
    }
    return res;
}

int main () 
{
    clock_t start, end;
    string time;
    crow::SimpleApp app;

    CROW_ROUTE(app, "/BagRandom/<int>/<int>")([&](int size, int w) {
        Backpack bag(w);
        NTreeForBag tree;
        start = clock();
        ArraySequence<Item>* arr = RandomItems(size);
        tree.TreeBag(arr, &bag);
        end = clock();
        time = to_string((int)(end - start) / (CLOCKS_PER_SEC / 1000)) + " ms";
        delete arr;
        crow_json data;
        data["Bag"] = crow_json::list({ (int)(bag.GetBC()), (int)(bag.GetW()), (int)(bag.GetC()) });
        crow_json::list items;
        std:vector<std::string> tmp = StringItems(bag.GetItems());
        for (auto k : tmp)
        {
            crow_json hhh = crow_json({ {"data", k} });
            items.push_back( hhh );
        }
        data["Items"] = crow_json(items);
        data["TimeBag"] = crow_json::list({ time });
        crow_json::list weight, cost, label;
        for (int i = 0; i < bag.GetItems()->GetLenght(); i++)
        {
            weight.push_back((int)(bag.GetItems()->Get(i).GetWeight()));
            cost.push_back((int)(bag.GetItems()->Get(i).GetCost()));
            label.push_back( i+1 );
        }
        data["Weight"] = crow_json(weight);
        data["Cost"] = crow_json(cost);
        data["Label"] = crow_json(label);
        delete bag.GetItems();
        crow::response ans(data);
        ans.add_header("Access-Control-Allow-Origin", "*");
        return ans;
    });

    CROW_ROUTE(app, "/BinSearch/<int>")([&](int key) {
        vector<int> resSearch, resTime;
        for (int i = 1000; i <= 10000; i += 1000)
        {
            int tmp_size = i;
            int* tmp_arr = new int[tmp_size];
            for (int j = 0; j < tmp_size; j++)
                tmp_arr[j] = rand() % 1000;
            start = clock();
            ArraySequence<int> tmp_arrSeq(tmp_arr, tmp_size);
            int flag = BinSearch<int>::Search(&tmp_arrSeq, key);
            end = clock();
            resSearch.push_back(flag);
            resTime.push_back(((int)(end - start) / (CLOCKS_PER_SEC / 1000)));
        }
        crow_json data;
        crow_json::list graphTime, search;
        for (auto k: resTime)
            graphTime.push_back(k);
        data["Time"] = crow_json(graphTime);
        for (auto k : resSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["Search"] = crow_json(search);
        
        crow::response ans(data);
        ans.add_header("Access-Control-Allow-Origin", "*");
        return ans;
    });

    CROW_ROUTE(app, "/BTreeSearch/<int>")([&](int key) {
        vector<int> resSearch, resTime;
    for (int i = 1000; i <= 10000; i += 1000)
    {
        int tmp_size = i;
        int* tmp_arr = new int[tmp_size];
        for (int j = 0; j < tmp_size; j++)
            tmp_arr[j] = rand() % 1000;
        start = clock();
        ArraySequence<int> tmp_arrSeq(tmp_arr, tmp_size);
        BTree btree = BTreeCreate();
        for (int i = 0; i < tmp_arrSeq.GetLenght(); i++)
            BTreeInsert(btree, tmp_arrSeq.Get(i));
        int flag = BTreeSearch(btree, key);
        end = clock();
        BTreeDestroy(btree);
        resSearch.push_back(flag);
        resTime.push_back(((int)(end - start) / (CLOCKS_PER_SEC / 1000)));
        }
        crow_json data;
        crow_json::list graphTime, search;
        for (auto k : resTime)
            graphTime.push_back(k);
        data["Time"] = crow_json(graphTime);
        for (auto k : resSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["Search"] = crow_json(search);

        crow::response ans(data);
        ans.add_header("Access-Control-Allow-Origin", "*");
        return ans;
    });

    CROW_ROUTE(app, "/BinTreeSearch/<int>")([&](int key) {
        vector<int> resSearch, resTime;
        for (int i = 1000; i <= 10000; i += 1000)
        {
            int tmp_size = i;
            int* tmp_arr = new int[tmp_size];
            for (int j = 0; j < tmp_size; j++)
                tmp_arr[j] = rand() % 1000;
            start = clock();
            BinaryTree<int> tree(tmp_arr, tmp_size);
            int flag = tree.Find(key);
            end = clock();
            resSearch.push_back(flag);
            resTime.push_back(((int)(end - start) / (CLOCKS_PER_SEC / 1000)));
        }
        crow_json data;
        crow_json::list graphTime, search;
        for (auto k : resTime)
            graphTime.push_back(k);
        data["Time"] = crow_json(graphTime);
        for (auto k : resSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["Search"] = crow_json(search);

        crow::response ans(data);
        ans.add_header("Access-Control-Allow-Origin", "*");
        return ans;
    });

    CROW_ROUTE(app, "/CombSearch/<int>")([&](int key) {
        vector<int> resSearchBinSearch, resTimeBinSearch, resSearchBinTreeSearch, 
                    resTimeBinTreeSearch, resSearchBTreeSearch, resTimeBTreeSearch;
        clock_t startBinSearch, endBinSearch, startBinTreeSearch, 
                endBinTreeSearch, startBTreeSearch, endBTreeSearch;
        for (int i = 1000; i <= 10000; i += 1000)
        {
            int tmp_size = i;
            int* tmp_arr = new int[tmp_size];
            for (int j = 0; j < tmp_size; j++)
                tmp_arr[j] = rand() % 1000;

            startBinSearch = clock();
            ArraySequence<int> arr(tmp_arr, tmp_size);
            int flagBinSearch = BinSearch<int>::Search(&arr, key);
            endBinSearch = clock();
            resSearchBinSearch.push_back(flagBinSearch);
            resTimeBinSearch.push_back(((int)(endBinSearch - startBinSearch) / (CLOCKS_PER_SEC / 1000)));

            startBinTreeSearch = clock();
            BinaryTree<int> tree(tmp_arr, tmp_size);
            int flagBinTreeSearch = tree.Find(key);
            endBinTreeSearch = clock();
            resSearchBinTreeSearch.push_back(flagBinTreeSearch);
            resTimeBinTreeSearch.push_back(((int)(endBinTreeSearch - startBinTreeSearch) / (CLOCKS_PER_SEC / 1000)));

            startBTreeSearch = clock();
            BTree btree = BTreeCreate();
            for (int i = 0; i < arr.GetLenght(); i++)
                BTreeInsert(btree, arr.Get(i));
            int flagBTreeSearch = BTreeSearch(btree, key);
            endBTreeSearch = clock();
            resSearchBTreeSearch.push_back(flagBTreeSearch);
            resTimeBTreeSearch.push_back(((int)(endBTreeSearch - startBTreeSearch) / (CLOCKS_PER_SEC / 1000)));
        }
        crow_json data;
        crow_json::list graphTime, search;

        for (auto k : resTimeBinSearch)
            graphTime.push_back(k);
        data["TimeBinSearch"] = crow_json(graphTime);
        for (auto k : resSearchBinSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["SearchBinSearch"] = crow_json(search);
        graphTime.clear();
        search.clear();

        for (auto k : resTimeBinTreeSearch)
            graphTime.push_back(k);
        data["TimeBinTreeSearch"] = crow_json(graphTime);
        for (auto k : resSearchBinTreeSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["SearchBinTreeSearch"] = crow_json(search);
        graphTime.clear();
        search.clear();

        for (auto k : resTimeBTreeSearch)
            graphTime.push_back(k);
        data["TimeBTreeSearch"] = crow_json(graphTime);
        for (auto k : resSearchBTreeSearch)
        {
            if (k == 1)
                search.push_back("Yes ");
            if (k == 0)
                search.push_back("No ");
        }
        data["SearchBTreeSearch"] = crow_json(search);

        crow::response ans(data);
        ans.add_header("Access-Control-Allow-Origin", "*");
        return ans;
    });

    app.port(1337)
        .server_name("CrowCpp")
        .multithreaded()
        .run();
}
