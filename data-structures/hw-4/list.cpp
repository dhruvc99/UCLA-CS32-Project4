// list.cpp
// Dhruv Chakraborty
// UID: 204-962-098
// Prof. Smallberg
// CS32 Winter19 HW4 problem 3(a)

void listAll(const MenuItem* m, string path) // two-parameter overload
{
	if (m->name() != "")
	{
		if (path != "")
			path += '/';
		path += m->name();
		cout << path << endl;
	}

    if (m->menuItems() == nullptr || m->menuItems()->empty())
		return;


	for (int i = 0; i < m->menuItems()->size(); i++)
		listAll((*m->menuItems())[i], path);
}
