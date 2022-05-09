 
#include "btree.h"

int main()
{
 
	int order = 0;
	while (order != 7)
	{
		puts("---------------------------------------------------------------------");
		puts("Select menu");
		puts("1:Creat a new 3-B-tree");
		puts("2:Insert element");
		puts("3:Find element");
		puts("4:Delete element");
		puts("5:Print B-tree");
		puts("6:exit");
		cin >> order;
		switch (order)
		{
		case 1: {Destory(T); creat_btree(); break; }
		case 2: {insert_keytype(); break; }
		case 3: {find_keytype(); break; }
		case 4: {delete_keytype(); break; }
		case 5: {show_Btree(T); puts(""); break; }
		case 6: {return 0; }
		}
	}
	return 0;
}
