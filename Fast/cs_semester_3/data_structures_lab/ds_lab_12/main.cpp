#include <iostream>
using namespace std;
#include <string>

int main(){

  HashMap<string> *map;
  map=new HashMap<string>;
  populateHash("students.txt", map);
  cout<<*map->get(9);
  map->deleteKey(9);
  assert(map->get(9)==nullptr);
  delete map;
	
  map=new QHashMap<string>;
  populateHash("students.txt", map);
  cout<<*map->get(98);
  map->deleteKey(98);
  assert(map->get(98)==nullptr);
  delete map;

  map=new DHashMap<string>;
  populateHash("students.txt", map);
  cout<<*map->get(101);
  map->deleteKey(101);
  assert(map->get(101)==nullptr);
  delete map;

  return 0;

}
