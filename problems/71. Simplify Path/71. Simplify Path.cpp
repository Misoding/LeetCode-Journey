class Solution {
public:
    string simplifyPath(string path) {
        deque<string> pathSt;
        pathSt.push_back("/");
        for(int i = 0; i < path.length();i++) {
            string formedString = "";
            if(path[i] == '/') continue;
            if (!pathSt.empty() && pathSt.back() == "/") {
                int start = i;
                while(i < path.length() && path[i] != '/') i++;
                formedString = path.substr(start, i-start);
                if (formedString == ".."){
                    pathSt.pop_back();
                    if ((pathSt.empty())) {
                        pathSt.push_back("/");
                        continue;
                    }
                    pathSt.pop_back();
                    continue;
                }
                if(formedString == "."){
                    continue;
                }
                pathSt.push_back(formedString);
                pathSt.push_back("/");
            }
        }
       string resString = "";
       pathSt.pop_back();
        while(!(pathSt.empty())) {
            resString += pathSt.front();
            pathSt.pop_front();
        }
        if (resString == "") return "/";

        return resString;

    }
};