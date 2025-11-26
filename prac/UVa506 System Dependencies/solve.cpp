// https://onlinejudge.org/external/5/506.pdf
#include <bits/stdc++.h>
using namespace std;

struct Component {
  vector<string> deps;
  bool installed = false;
  bool explicit_install = false;
  int dependents = 0;
};

unordered_map<string, Component> components;
vector<string> install_order;
unordered_set<string> in_order;

Component& ensure(const string& name) {
  return components[name];
}

void install(const string& name, bool explicit_request) {
  auto& comp = ensure(name);
  if (comp.installed) {
    if (explicit_request) {
      cout << name << " is already installed.\n";
    }
    return;
  }
  for (const auto& dep : comp.deps) install(dep, false);
  cout << "Installing " << name << "\n";
  comp.installed = true;
  comp.explicit_install = explicit_request;
  for (const auto& dep : comp.deps) ensure(dep).dependents++;
  if (!in_order.count(name)) {
    install_order.push_back(name);
    in_order.insert(name);
  }
}

bool can_remove(const string& name) {
  const auto& comp = components[name];
  return comp.installed && comp.dependents == 0;
}

void remove(const string& name, bool explicit_request) {
  auto& comp = components[name];
  if (!comp.installed) {
    if (explicit_request) {
      cout << name << " is not installed.\n";
    }
    return;
  }
  if (comp.dependents > 0) {
    if (explicit_request) {
      cout << name << " is still needed.\n";
    }
    return;
  }
  cout << "Removing " << name << "\n";
  comp.installed = false;
  comp.explicit_install = false;
  for (auto it = comp.deps.rbegin(); it != comp.deps.rend(); ++it) {
    auto& dep = ensure(*it);
    dep.dependents--;
    if (dep.dependents == 0 && !dep.explicit_install) {
      remove(*it, false);
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string line;
  while (getline(cin, line)) {
    cout << line << "\n";
    if (line == "END") break;
    stringstream ss(line);
    string cmd;
    ss >> cmd;
    if (cmd == "DEPEND") {
      string name;
      ss >> name;
      auto& comp = ensure(name);
      string dep;
      while (ss >> dep) {
        comp.deps.push_back(dep);
        ensure(dep);
      }
    } else if (cmd == "INSTALL") {
      string name;
      ss >> name;
      install(name, true);
    } else if (cmd == "REMOVE") {
      string name;
      ss >> name;
      if (!components.count(name)) {
        cout << name << " is not installed.\n";
      } else {
        remove(name, true);
      }
    } else if (cmd == "LIST") {
      for (const auto& name : install_order) {
        if (components[name].installed) {
          cout << name << "\n";
        }
      }
    }
  }
  return 0;
}
