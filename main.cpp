#include <bits/stdc++.h>

#include <utility>
#define ROW 3
#define COL 3
using namespace std;
using namespace std::chrono;


class State{
private:
    vector<vector<int>> v;
    pair<int,int> emptySpace;
    State* parent;
    string step;
    int cost;
    int totalCost;
public:

    State(vector<vector<int>> v, pair<int,int> emptySpace, State* parent, string step, int cost){
        this->v = v;
        this->emptySpace = emptySpace;
        this->parent = parent;
        this->step = step;
        this->cost = cost;
    }
    vector<vector<int>> getValues(){
        return v;
    }

    pair<int,int> getEmptySpace(){
        return emptySpace;
    }

    State* getParent(){
        return parent;
    }

    int getCost(){
        return cost;
    }

    int getTotalCost(){
        return totalCost;
    }

    void print(){
        cout<<step<<endl;
        for(auto a : v){
            for(auto b : a){
                cout<<b<< " ";
            }
            cout<<endl;
        }
    }
};

State* goal;
set<vector<vector<int>>> visited;
bool isGoal(State* state1){
    return state1->getValues() == goal->getValues();
}
pair<int,int> locateEmpty(vector<vector<int>> v){
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            if(v[i][j]==0){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}

vector<State*> getPath(State* current){
    stack<State*> s;
    while(current != nullptr){
        s.push(current);
        current = current->getParent();
    }
    vector<State*> ret;
    while(!s.empty()){
        ret.push_back(s.top());
        s.pop();
    }
    return ret;
}

void foundGoal(State* current, int expanded){
    cout << "Cost: "<< current->getCost() << endl;
    cout << "Expanded: " << expanded << endl;
    cout << "Search Depth: " << current->getCost() << endl;
    char choice;
    cout<<"Print path?(y/n)"<<endl;
    cin >> choice;
    choice = (char)tolower(choice);
    if(choice == 'y') {
        cout << "\nPath is:\n";
        for(State* state : getPath(current)){
            state->print();
            cout<<endl;
        }
    }
}

void bfs(State* current){
    auto start = high_resolution_clock::now();
    queue<State*> q;
    q.push(current);
    visited.insert(current->getValues());
    int cost = 0;
    int expanded = 0;
    while(!q.empty()){
        int len = q.size();
        while(len--) {
            current = q.front();
            q.pop();
            expanded++;
            //current->print();
            //cout<<endl<<++counter<<endl<<endl;
            if (isGoal(current)) {
                auto end = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(end - start);
                cout << "Goal reached\n";
                cout << "Runtime: " << duration.count() << " milliseconds" << endl;
                foundGoal(current,expanded);
                return;
            }

            int i = current->getEmptySpace().first, j = current->getEmptySpace().second;

            //generate all 4 new states if possible and add to queue if not visited
            if (i > 0) {
                vector<vector<int>> neighbor = current->getValues();
                swap(neighbor[i][j], neighbor[i - 1][j]);
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(new State(neighbor, {i - 1, j}, current,"UP", 1 + current->getCost()));
                }
            }
            if (i < ROW - 1) {
                vector<vector<int>> neighbor = current->getValues();
                swap(neighbor[i][j], neighbor[i + 1][j]);
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(new State(neighbor, {i + 1, j}, current,"DOWN", 1 + current->getCost()));
                }
            }
            if (j > 0) {
                vector<vector<int>> neighbor = current->getValues();
                swap(neighbor[i][j], neighbor[i][j - 1]);
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(new State(neighbor, {i, j - 1}, current,"LEFT", 1 + current->getCost()));
                }
            }
            if (j < COL - 1) {
                vector<vector<int>> neighbor = current->getValues();
                swap(neighbor[i][j], neighbor[i][j + 1]);
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    q.push(new State(neighbor, {i, j + 1}, current,"RIGHT", 1 + current->getCost()));
                }
            }
        }
    }
}

void dfs(State* current){
    auto start = high_resolution_clock::now();
    stack<State*> s;
    s.push(current);
    visited.insert(current->getValues());
    int expanded = 0;
    while(!s.empty()){
        current = s.top();
        s.pop();
        expanded++;
        if (isGoal(current)) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Goal reached\n";
            cout << "Runtime: " << duration.count() << " milliseconds" << endl;
            foundGoal(current,expanded);
            return;
        }

        int i = current->getEmptySpace().first, j = current->getEmptySpace().second;

        //generate all 4 new states if possible and add to queue if not visited
        if (i > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i - 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                s.push(new State(neighbor, {i - 1, j}, current,"UP",current->getCost()+1));
            }
        }
        if (i < ROW - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i + 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                s.push(new State(neighbor, {i + 1, j}, current,"DOWN",current->getCost()+1));
            }
        }
        if (j > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j - 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                s.push(new State(neighbor, {i, j - 1}, current,"LEFT",current->getCost()+1));
            }
        }
        if (j < COL - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j + 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                s.push(new State(neighbor, {i, j + 1}, current,"RIGHT",current->getCost()+1));
            }
        }
    }
}
unordered_map<int,pair<int,int>> locations;

int manhattanHeuristic(vector<vector<int>> v){
    int manhattanDistance = 0;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            pair<int,int> cur = locations[v[i][j]];
            if(cur.first!=i || cur.second!=j){
                manhattanDistance += (abs(cur.first-i) + abs(cur.second-j));
            }
        }
    }
    return manhattanDistance;
}

int euclideanHeuristic(vector<vector<int>> v){
    double euclideanDistance = 0;
    for(int i=0;i<3;++i){
        for(int j=0;j<3;++j){
            pair<int,int> cur = locations[v[i][j]];
            if(cur.first!=i && cur.second!=j){
                euclideanDistance += (sqrt(pow(cur.first-i,2) + pow(cur.second-j,2)));
            }
        }
    }
    return euclideanDistance;
}

void astarManhattan(State* current){
    auto start = high_resolution_clock::now();
    //int heuristics = manhattan ? manhattanHeuristic(current->getValues()) : euclideanHeuristic(current->getValues());
    visited.insert(current->getValues());
    int expanded = 0;
    priority_queue<pair<int,State*>, vector<pair<int,State*>>, greater< pair<int, State*> > > pq;
    pq.push({manhattanHeuristic(current->getValues())+current->getCost(),current});
    while(!pq.empty()){
        current = pq.top().second;
        pq.pop();
        expanded++;
        if (isGoal(current)) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Goal reached\n";
            cout << "Runtime: " << duration.count() << " milliseconds" << endl;
            foundGoal(current,expanded);
            return;
        }

        int i = current->getEmptySpace().first, j = current->getEmptySpace().second;

        //generate all 4 new states if possible and add to queue if not visited
        if (i > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i - 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({manhattanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i - 1, j}, current,"UP",current->getCost()+1)});
            }
        }
        if (i < ROW - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i + 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({manhattanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i + 1, j}, current,"DOWN",current->getCost()+1)});
            }
        }
        if (j > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j - 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({manhattanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i, j - 1}, current,"LEFT",current->getCost()+1)});
            }
        }
        if (j < COL - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j + 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({manhattanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i, j + 1}, current,"RIGHT",current->getCost()+1)});
            }
        }
    }
}

void astarEuclidean(State* current){
    auto start = high_resolution_clock::now();
    //int heuristics = manhattan ? manhattanHeuristic(current->getValues()) : euclideanHeuristic(current->getValues());
    visited.insert(current->getValues());
    int expanded = 0;
    priority_queue<pair<double,State*>, vector<pair<double,State*>>, greater< pair<double, State*> > > pq;
    pq.push({euclideanHeuristic(current->getValues())+current->getCost(),current});
    while(!pq.empty()){
        current = pq.top().second;
        pq.pop();
        expanded++;
        if (isGoal(current)) {
            auto end = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(end - start);
            cout << "Goal reached\n";
            cout << "Runtime: " << duration.count() << " milliseconds" << endl;
            foundGoal(current,expanded);
            return;
        }

        int i = current->getEmptySpace().first, j = current->getEmptySpace().second;

        //generate all 4 new states if possible and add to queue if not visited
        if (i > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i - 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({euclideanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i - 1, j}, current,"UP",current->getCost()+1)});
            }
        }
        if (i < ROW - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i + 1][j]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({euclideanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i + 1, j}, current,"DOWN",current->getCost()+1)});
            }
        }
        if (j > 0) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j - 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({euclideanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i, j - 1}, current,"LEFT",current->getCost()+1)});
            }
        }
        if (j < COL - 1) {
            vector<vector<int>> neighbor = current->getValues();
            swap(neighbor[i][j], neighbor[i][j + 1]);
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                pq.push({euclideanHeuristic(neighbor)+current->getCost(),new State(neighbor, {i, j + 1}, current,"RIGHT",current->getCost()+1)});
            }
        }
    }
}


void generateRandomly(vector<vector<int>>& initial){
    /*unordered_set<int> taken;
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            int num;
            do{
                num = rand()%9;
            }while(taken.count(num));
            initial[i][j] = num;
        }
    }*/
    vector<int> nums = {0,1,2,3,4,5,6,7,8};
    random_device rd;
    mt19937 g(rd());
    shuffle(nums.begin(),nums.end(),g);
    int k = 0;
    for(int i=0;i<ROW;++i){
        for(int j=0;j<COL;++j){
            initial[i][j] = nums[k++];
        }
    }
}
int getInvCount(vector<int> arr) {
    int inv_count = 0;
    for (int i = 0; i < 9; i++)
        for (int j = i+1; j < 9; j++)
            if (arr[j] && arr[i] &&  arr[i] > arr[j])
                inv_count++;
    return inv_count;
}

// This function returns true if given 8 puzzle is solvable.
bool isSolvable(vector<vector<int>> p) {
    vector<int> puzzle(9);
    int k=0;
    for(int i=0;i<3;++i)
        for(int j=0;j<3;++j)
            puzzle[k++] = p[i][j];
    // Count inversions in given 8 puzzle and return true if inversion count is even.
    return (getInvCount(puzzle)%2 == 0);
}
int main() {
    goal = new State({{0,1,2},{3,4,5},{6,7,8}},{0,0},nullptr,"",0);
    //goal = new State({{1,2,3},{4,5,6},{7,8,0}},{0,0},nullptr,"");
    vector<vector<int>> v(ROW, vector<int>(COL));
    locations[0]={0,0};
    locations[1]={0,1};
    locations[2]={0,2};
    locations[3]={1,0};
    locations[4]={1,1};
    locations[5]={1,2};
    locations[6]={2,0};
    locations[7]={2,1};
    locations[8]={2,2};
    while(true){
        unsigned int choice = 0;
        cout<<"Generate values:\n1 - Manually\n2 - Automatically\n3 - Exit\n";
        do{
            cin>>choice;
        }while(choice != 1 && choice != 2 && choice != 3);
        if(choice == 1) {
            pair<int,int> emptySpace;
            while(true){
                cout << "Enter values for initial state: \n";
                for (int i = 0; i < ROW; ++i)
                    for (int j = 0; j < COL; ++j) {
                        cin >> v[i][j];
                        if(v[i][j] == 0)
                            emptySpace = {i,j};
                    }
                if(isSolvable(v)) break;
                else cout << "Unsolvable state, please re-enter values.\n";
            }
        }
        else if(choice == 2){
            generateRandomly(v);
        }else{
            return 0;
        }
        State* state = new State(v,locateEmpty(v),nullptr,"INITIAL",0);

        choice = 0;

        cout << "Solve using:" << endl << "1 - BFS\n2 - DFS\n3 - A* Manhattan\n4 - A* Euclidean\n";
        cin>>choice;
        switch(choice){
            case 1:
                visited.clear();
                bfs(state);
                break;
            case 2:
                visited.clear();
                dfs(state);
                break;
            case 3:
                visited.clear();
                astarManhattan(state);
                break;
            case 4:
                visited.clear();
                astarEuclidean(state);
                break;
            default:
                cout<<"Invalid entry.\n";
        }
    }
}
