#include <cassert>
#include <iostream>
#include <list>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

class File {
   protected:
    std::string m_path;
    int m_size;
    File *m_parent;
    bool m_isdir;

   public:
    File(std::string path, int size, File *parent = nullptr, bool isdir = false)
        : m_path{path}, m_size{size}, m_parent{parent}, m_isdir{isdir} {
        if (!parent) return;
        if (!parent->parent()) {
            m_path = "/" + m_path;
            return;
        }
        m_path = parent->path() + "/" + m_path;
    };

    // File(const File &f) = default;
    File(const File &f) = delete;
    File(File &&) = default;

    File *parent() const { return m_parent; }
    const std::string &path() const { return m_path; }
    int size() const { return m_size; }
    bool isdir() const { return m_isdir; }
};

std::ostream &operator<<(std::ostream &o, const File &f) {
    o << "path: " << f.path() << ", size: " << f.size();
    return o;
}

class Directory : public File {
    std::list<const File *> m_files{};
    std::list<const Directory *> m_children{};

    static void increment_size(Directory *d, size_t size) {
      if(d->parent()) Directory::increment_size(static_cast<Directory*>(d->parent()), size);
      d->m_size += size;
    }

   public:
    // Directory(const File &file) : File{file} {};
    Directory(File &&file) : File{std::move(file)} {};


    void add_file(File &f) {
        m_files.push_back(&f);
        Directory::increment_size(this, f.size());
    }

    void add_directory(const Directory &d) { m_children.push_back(&d); }

    const std::list<const File*> & files() const { return m_files; }
};

const File make_path(const std::string &s, File *current_path) {
    std::stringstream ss{s};
    std::string t;
    std::vector<std::string> tokens;
    while (std::getline(ss, t, ' ')) tokens.push_back(t);
    assert(s.at(0) != '$');
    assert(tokens.size() == 2);

    std::string &filename = tokens[1];
    std::string &size = tokens[0];

    if (size == "dir") return File(filename, 0, current_path, true);
    return File(filename, std::stoi(size), current_path, false);
}

int main() {
    std::string l;
    std::vector<std::string> lines;
    while (std::getline(std::cin, l)) lines.push_back(l);

    std::list<Directory> dirs{};
    std::list<File> files{};

    Directory *current_dir = nullptr;

    for (auto &l : lines) {
        std::cout << "input: " << l << std::endl;
        auto cmd = l.substr(0, 4);

        if (cmd == "$ cd") {
            std::string dirname{l.substr(5)};

            if (dirname == "..") {
              current_dir = static_cast<Directory*>(current_dir->parent());
              continue;
            }

            // if (dirname == "/") current_dir = nullptr;
            File f{dirname, 0, current_dir, true};
            dirs.emplace_back(std::move(f));
            current_dir = &dirs.back();
            std::cout << "Current dir: " << current_dir << ' ' << current_dir->path() << '\n';
            continue;
        }
        if (cmd == "$ ls") continue;

        assert(current_dir);
        assert(!current_dir->path().empty());

        auto cd = current_dir;
        File f = make_path(l, cd);

        if (f.isdir()) {
            dirs.emplace_back(std::move(f));
            current_dir->add_directory(dirs.back());
        } else {
            files.emplace_back(std::move(f));
            current_dir->add_file(files.back());
        }
        // return 0;
    }

    std::cout << "\n\ndirs\n";
    for (auto &d : dirs) std::cout << d << ",  #files: " << d.files().size() << '\n';

    return 0;
}
