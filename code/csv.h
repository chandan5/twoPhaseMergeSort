class CSVFile
{
    public:
        string filepath;
        vector<vector<string> > filedata;
        // ifstream file(const char * a);
        CSVFile(string file_path) {
            filepath = file_path;
        }
        void print();
        bool fillNextLineAfterSplittingIntoTokens(ifstream& file)
        {
            vector<string> row;
            string line;
            getline(file,line);
            stringstream lineStream(line);
            string cell;
            bool isEmpty = true;
            while(getline(lineStream,cell,','))
            {
                row.pb(cell);
                isEmpty = false;
            }
            if(row.size() != 0)
                filedata.pb(row);
            return !isEmpty;
        }

        vector<vector<string> > * getAllLines()
        {
            ifstream file(filepath);
            while(fillNextLineAfterSplittingIntoTokens(file));
            return &filedata;
        }
        int num_rows()
        {
            int rows = filedata.size();
            return rows;
        }
        int num_cols()
        {
            int cols = num_rows() ? filedata[0].size() : 0;
            return cols;
        }
};

class CSVMetaData: public CSVFile
{
    public:
        vector<string> metadata;
        vector<int> metadata_map;
        using CSVFile::CSVFile;
        int size=0; // in bytes
        vector<string> getMetaData()
        {
            getAllLines();
            vector<string> ret;
            int rows = num_rows();
            size = 0;
            for(int row=0; row<rows; row++)
            {
                if(filedata[row][1] == "date")
                {
                    ret.pb(filedata[row][1]);
                    size += sizeof(Date);
                }
                else if(filedata[row][1] == "int")
                {
                    ret.pb(filedata[row][1]);
                    size += sizeof(int);
                }
                else
                {
                    ret.pb("string");
                    int chars_in_string = stoi(filedata[row][1].substr(5,filedata[row][0].size()-6));
                    size += sizeof(string) + chars_in_string;
                }
            }
            metadata = ret;
            return ret;
        }
        vector<int> getMetaDataMap()
        {
            int ints_count=0, strings_count=0, dates_count=0;
            int n = metadata.size();
            for (int col = 0; col < n; col++) {
                if(metadata[col] == "string")
                {
                    metadata_map.pb(strings_count);
                    strings_count++;
                }
                else if(metadata[col] == "int")
                {
                    metadata_map.pb(ints_count);
                    ints_count++;
                }
                else if(metadata[col] == "date")
                {
                    metadata_map.pb(dates_count);
                    dates_count++;
                }
            }
            return metadata_map;
        }
};

class CSVRelation: public CSVFile
{
    public:
        using CSVFile::CSVFile;
        ll getAllRowsCount()
        {
            ll count = 0;
            ifstream file(filepath);
            vector<string> nextLine;
            while(1)
            {
                nextLine = getNextLineAndSplitIntoTokens(file);
                if(nextLine.size() == 0)
                    break;
                else
                    count++;
            }
            return count;
        }
        vector<string> getNextLineAndSplitIntoTokens(ifstream& file)
        {
            vector<string> row;
            string line;
            getline(file,line);
            stringstream lineStream(line);
            string cell;
            while(getline(lineStream,cell,','))
                row.pb(cell);
            return row;
        }
        vector<Row> getRows(vector<string> metadata, int required_rows, ifstream& file)
        {
            vector<Row> rows;
            vector<string> nextLine;
            ll count = 0;
            while(1)
            {
                nextLine = getNextLineAndSplitIntoTokens(file);
                if(nextLine.size() == 0)
                    break;
                else
                {
                    vector<int> ints;
                    vector<string> strings;
                    vector<Date> dates;
                    int n = metadata.size();
                    for(int i=0;i<n;i++)
                    {
                        if(metadata[i] == "string")
                            strings.pb(nextLine[i]);
                        else if(metadata[i] == "int")
                            ints.pb(stoi(nextLine[i]));
                        else
                            dates.pb(Date(nextLine[i]));
                    }
                    rows.pb(Row(ints,strings,dates));
                    count++;
                    if(count >= required_rows)
                        break;
                }
                // cout << count << endl;
            }
            return rows;
        }
};
