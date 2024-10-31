// landmark.cpp
// Dhruv Chakraborty, UID: 204-962-098
// UCLA CS32, HW3: part 1

class Landmark
{
	public:
		Landmark(string name): m_name(name) {} 
		virtual ~Landmark() {}
		virtual string color() const {return "yellow";} // return yellow as default since we only return blue in case of hospital
		virtual string icon() const = 0; // pure virtual function so that we can't initialize ambigious Landmark -- must have a specific Landmark
		string name() const {return m_name;}
	private:
		string m_name;
};

class Hotel : public Landmark
{
	public:
		Hotel(string name): Landmark(name) {}

		virtual ~Hotel()
		{
			cout << "Destroying the hotel " << name() << "." << endl;
		}

		virtual string icon() const {return "bed";}
};

class Restaurant : public Landmark
{
	public: 
		Restaurant(string name, int seatCap) : Landmark(name), m_seats(seatCap) {}

		virtual ~Restaurant()
		{
			cout << "Destroying the restaurant " << name() << "." << endl;
		}

		virtual string icon() const 
		{
			if (m_seats < 40) {return "small knife/fork";}
			else {return "large knife/fork";}
		}

	private:
		int m_seats;
};

class Hospital : public Landmark
{
	public:
		Hospital(string name) : Landmark(name) {}

		virtual ~Hospital()
		{
			cout << "Destroying the hospital " << name() << "." << endl;
		}

		virtual string icon() const {return "H";}

		virtual string color() const {return "blue";}
};