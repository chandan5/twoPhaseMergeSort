
// using namespace std;

class Row {
    public:
        vector<int> ints;
        vector<string> strings;
        vector<Date> dates; // need to change data type
        Row(vector<int> i, vector<string> s, vector<Date> d)
        {
            ints = i;
            strings = s;
            dates = d;
        }
        Row(unsigned int ints_count = 0,    //useless constructor
            unsigned int strings_count = 0,
            unsigned int dates_count = 0,
            unsigned int size_of_string = 0){
            ints = vector<int>(ints_count);
            strings = vector<string> (strings_count, string(size_of_string,'a'));
            // strings = vector<string> (strings_count);
            dates = vector<Date>(dates_count);
        }
        int size()
        {   return ints.size() + strings.size() + dates.size();}
        void print();
        void print(ofstream& output_stream);
        void printCols(ofstream& output_stream);
        bool operator<(const Row r2) const
        {
            int comp_size = comp_cols.size();
            for (int i = 0; i < comp_size; i++) {
                int col = comp_cols[i];
                // Logically this is happening
                // if(r1[col] == r2[col])
                //     continue;
                // else
                //     return r1[col] < r2[col];
                if(metadata[col] == "string")
                {
                    string s1 = strings[metadata_map[col]];
                    string s2 = r2.strings[metadata_map[col]];
                    if(s1 == s2)
                        continue;
                    else
                        return s1 < s2;
                }
                else if(metadata[col] == "int")
                {
                    int a = ints[metadata_map[col]];
                    int b = r2.ints[metadata_map[col]];
                    if(a == b)
                        continue;
                    else
                        return a < b;
                }
                else if(metadata[col] == "date")
                {
                    Date d1 = dates[metadata_map[col]];
                    Date d2 = r2.dates[metadata_map[col]];
                    if(d1 == d2)
                        continue;
                    else
                        return d1 < d2;
                }
            }
            return false;
        }
};
