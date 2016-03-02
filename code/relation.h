class Relation {
    public:
        vector<Row> rows;
        vector<string> * rel_metadata;
        ll num_rows_in_file=0;
        CSVRelation * csv_rel;
        Relation(CSVRelation * csvRel, vector<string> * metadata)//, ll rowIter)
        {
            csv_rel = csvRel;
            num_rows_in_file = csv_rel->getAllRowsCount();
            rel_metadata = metadata;
            // rows = csv_rel.getAllRows(metadata);
        }
        void readRows(ifstream& file, int required_rows)
        {
            rows = csv_rel->getRows(*rel_metadata,required_rows,file);
        }
        void writeLines(ofstream& file)
        {

        }
        void clearRows()
        {
            rows.clear();
        }
        void sort(int desc)
        {
            if(!desc)
                stable_sort(rows.begin(),rows.end());
            else
                stable_sort(rows.rbegin(),rows.rend());
        }
        void print();
        void printCols(ofstream& file)
        {
            int n = rows.size();
            for(int i=0;i<n;i++)
            {
                rows[i].printCols(file);
            }
        }
        void print(ofstream& file)
        {
            int n = rows.size();
            for(int i=0;i<n;i++)
            {
                rows[i].print(file);
            }
        }
        void tempStore(string filePath)
        {

        }
};
