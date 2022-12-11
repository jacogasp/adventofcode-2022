#include <algorithm>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class Object {
   private:
    std::string m_name;
    std::string m_abspath;
    size_t m_size;
    Object *m_parent;

   public:
    Object(const std::string &name, size_t size = 0, Object *parent = nullptr)
        : m_name{name}, m_size{size}, m_parent{parent} {
        if (parent) {
            m_abspath = parent->parent() ? parent->abspath() + "/" + name : "/" + name;
        } else {
            m_abspath = name;
        }
    }
    void increment_size(size_t size) { m_size += size; }
    size_t size() const { return m_size; }
    Object *parent() { return m_parent; }
    const std::string &name() const { return m_name; }
    const std::string &abspath() const { return m_abspath; }
};

class File : public Object {
   public:
    File(const std::string &name, size_t size = 0, Object *parent = nullptr) : Object(name, size, parent){};
};

class Directory : public Object {
    std::map<std::string, Object *> m_children{};

    static void add_filesize(size_t size, Directory *d) {
        if (d == nullptr) return;
        add_filesize(size, static_cast<Directory *>(d->parent()));
        d->increment_size(size);
    }

   public:
    Directory(const std::string &name, size_t size = 0, Directory *parent = nullptr) : Object(name, size, parent){};

    void add_child(Object &obj) {
        m_children.insert({obj.name(), &obj});
        add_filesize(obj.size(), this);
    }

    void ls(bool fullpath = false) {
        std::cout << "$ ls " << (fullpath ? abspath() : name()) << std::endl;
        for (auto &c : m_children) std::cout << "  " << c.first << ' ' << c.second->size() << std::endl;
        std::cout << "size: " << size() << std::endl;
    }

    Object *child(const std::string &name) {
        if (auto found = m_children.find(name); found != m_children.end()) return found->second;
        return nullptr;
    }
};

struct TokenPair {
    std::string first;
    std::string last;
};

using Tokens = std::vector<std::string>;

Tokens tokenize(const std::string &s) {
    std::stringstream ss{s};
    std::string t;
    Tokens tokens;
    while (std::getline(ss, t, ' ')) tokens.push_back(t);
    return tokens;
}

Directory *cd(const std::string &dirname, Directory *current_dir, Directory *root) {
    if (dirname == "/") return root;
    if (dirname == "..") return current_dir->parent() ? static_cast<Directory *>(current_dir->parent()) : root;
    if (auto child = current_dir->child(dirname)) return static_cast<Directory *>(child);
    return nullptr;
}

int main() {
    std::string input;
    std::list<File> files;
    std::list<Directory> dirs;

    dirs.emplace_back("/");

    Directory *root = &dirs.back();
    Directory *current_dir = root;

    while (std::getline(std::cin, input)) {
        std::string cmd{input.substr(0, 4)};

        if (cmd == "$ cd") {
            std::string dirname{input.substr(5)};
            if (Directory *next_dir = cd(dirname, current_dir, root))
                current_dir = next_dir;
            else
                std::cout << "item not found: " << dirname << std::endl;
            continue;
        }

        if (cmd == "$ ls") continue;

        auto tokens = tokenize(input);
        std::string &ssize = tokens.at(0);
        std::string &name = tokens.at(1);

        if (ssize == "dir") {
            dirs.emplace_back(name, 0, current_dir);
            current_dir->add_child(dirs.back());
        } else {
            size_t size = std::stoi(ssize);
            files.emplace_back(name, size, current_dir);
            current_dir->add_child(files.back());
        }
    }

    std::cout << std::endl;
    root->ls();
    std::cout << std::endl;

    constexpr size_t total_disk_size = 70000000;
    constexpr size_t update_size = 30000000;

    dirs.sort([](const Directory &a, const Directory &b) { return a.size() < b.size(); });

    size_t free_space = total_disk_size - root->size();
    size_t required_space = update_size - free_space;

    printf("Total disk space: %zu\n", total_disk_size);
    printf("Free space: %zu\n", free_space);
    printf("Required space: %zu\n", required_space);

    for (auto &dir : dirs) {
        if (dir.size() >= required_space) {
            std::cout << "Directory: " << dir.abspath() << ", size: " << dir.size() << std::endl;
            break;
        }
    }

    return 0;
}