#include <parser.hpp>

int main(int argc, char *argv[]) {
  if ( argc < 2 ) {
    std::cerr << "./executable <string>/path/to/file.txt";
    std::cerr << std::endl;
    exit(EXIT_FAILURE);
  }

  Parser parser(argv[1]);
  
  typedef std::string Key;
  Key tuple, data;

  int resp = 5;
  bool c = true;
  do {
    std::cout << "\n**** MENU ****\n\n";
    std::cout << " 1. Insert\n";
    std::cout << " 2. Remove\n";
    std::cout << " 3. Query\n";
    std::cout << " 4. Print\n";
    std::cout << " 0. Exit\n";
    std::cout << ">_ ";
    std::cin >> resp;
    switch (resp) {
      case 1:
        std::cout << "Insert NEW tuple (key1:key2:data) -> ";
        std::cin >> tuple;
        if (parser.insert(tuple))
            std::cout << "ok\n";
        break;

      case 2:
        std::cout << "\n*****WARNING*****\n";
        std::cout << "Insert tuple (key1:key2:data) to delete -> ";
        std::cin >> tuple;
        parser.remove(tuple);
        break;

      case 3:
        std::cout << "Search tuple (key1:key2:data) -> ";
        std::cin >> tuple;
        if (parser.search(tuple)) 
          std::cout << "****found****\n";
        else 
          std::cout << "****NOT found****\n";
        break;

      case 4:
        parser.print();
        break;

      case 0:
        c = false;
        break;

      default:
        std::cout << "Invalid option: retry\n";
        continue;
    }
  } while (c);

  exit(EXIT_SUCCESS);
}