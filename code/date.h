class Date {
    public:
        char date; // 12
        char month; // 12
        short int year; // 1995
        Date(): date(char(5)), month(char(3)), year(1995) {}
        Date(string d_str)
        {
            date = char(stoi(d_str.substr(0,2)));
            month = char(stoi(d_str.substr(3,2)));
            year = (short int) (stoi(d_str.substr(6,4)));
        }
        Date(char d, char m, short int y): date(d), month(m), year(d) {}
        bool operator<(const Date d2) const
        {
            if(year < d2.year || year > d2.year)
                return year < d2.year;
            if(month < d2.month || month > d2.month)
                return month < d2.month;
            return date < d2.date;
        }
        bool operator==(const Date d2) const
        {
            return (year == d2.year && month == d2.month && date == d2.date);
        }
        void print();
        void print(ofstream& output_stream)
        {
            if((int)date < 10)
                output_stream << "0";
            output_stream << (int)date;
            output_stream << "/";
            if((int)month < 10)
                output_stream << "0";
            output_stream << (int)month;
            output_stream << "/";
            output_stream << year;
            // output_stream << "\n";
        }
};
