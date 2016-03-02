//          AUTHOR : CHANDAN KHARBANDA
//          github.com/chandan5

#include<bits/stdc++.h>

using namespace std;

#define pb push_back
#define ll long long int



#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename __Tp1>
void __f(const char* name, __Tp1&& __tp1){
        cerr << name << " : " << __tp1 << std::endl;
}
template <typename __Tp1, typename... __Tps>
void __f(const char* names, __Tp1&& __tp1, __Tps&&... __tps){
        const char* comma = strchr(names + 1, ',');
            cerr.write(names, comma - names) << " : " <<  __tp1 << " | " ;
                __f(comma+1, __tps...);
}
#else
#define trace(...)
#endif

// GLOBAL VARIABLES
string METADATA_FILEPATH = "../metadata.txt";
string INPUT_FILEPATH; //= "../input.txt";
string OUTPUT_FILEPATH = "../input.txt";
int order = 0;
double mm=0;
vector<int> comp_cols;
vector<int> out_cols;
vector<string> metadata;
vector<int> metadata_map;
const ll INF = LLONG_MAX;

#include "date.h"
#include "row.h"
#include "csv.h"
#include "relation.h"

void CSVFile::print()
{
    int rows = num_rows();
    int cols = num_cols();
    cout << rows << " " << cols << endl;
    for(int row=0; row<rows; row++)
    {
        for(int col=0; col<cols; col++)
            cout << filedata[row][col] << " ";
        cout << endl;
    }
}
void Date::print() {
    cout << int(date) << "/" << int(month) << "/" << year;// << endl;
}

void Row::print() {
    int n = metadata_map.size();
    for (int col = 0; col < n-1; col++) {
        if(metadata[col] == "string")
            cout << strings[metadata_map[col]] << ",";
        else if(metadata[col] == "int")
            cout << ints[metadata_map[col]] << ",";
        else if(metadata[col] == "date")
        {
            dates[metadata_map[col]].print(); cout << ",";
        }
    }
    int col = n-1;
    if(metadata[col] == "string")
        cout << strings[metadata_map[col]] << endl;
    else if(metadata[col] == "int")
        cout << ints[metadata_map[col]] << endl;
    else if(metadata[col] == "date")
    {    dates[metadata_map[col]].print(); cout << endl; }
}

void Row::print(ofstream& output_stream)
{
    int n = metadata_map.size();
    for (int col = 0; col < n-1; col++) {
        if(metadata[col] == "string")
            output_stream << strings[metadata_map[col]] << ",";
        else if(metadata[col] == "int")
            output_stream << ints[metadata_map[col]] << ",";
        else if(metadata[col] == "date")
        {
            dates[metadata_map[col]].print(output_stream); output_stream << ",";
        }
    }
    int col = n-1;
    if(metadata[col] == "string")
        output_stream << strings[metadata_map[col]] << endl;
    else if(metadata[col] == "int")
        output_stream << ints[metadata_map[col]] << endl;
    else if(metadata[col] == "date")
    {    dates[metadata_map[col]].print(output_stream); output_stream << endl; }
}

void Row::printCols(ofstream& output_stream)
{
    int n = out_cols.size(), col;
    for (int c = 0; c < n-1; c++) {
        col = out_cols[c];
        if(metadata[col] == "string")
            output_stream << strings[metadata_map[col]] << ",";
        else if(metadata[col] == "int")
            output_stream << ints[metadata_map[col]] << ",";
        else if(metadata[col] == "date")
        {
            dates[metadata_map[col]].print(output_stream); output_stream << ",";
        }
    }
    col = out_cols[n-1];
    if(metadata[col] == "string")
        output_stream << strings[metadata_map[col]] << endl;
    else if(metadata[col] == "int")
        output_stream << ints[metadata_map[col]] << endl;
    else if(metadata[col] == "date")
    {    dates[metadata_map[col]].print(output_stream); output_stream << endl; }
}


void Relation::print()
{
    int n = rows.size();
    for(int i=0;i<n;i++)
        rows[i].print();
}

void printV (vector<string> v){
  for (int i=0; i<v.size();i++){
    cout << v[i] << " : ";
  }
  cout << endl;
}

void printVs (vector<int> v) {
    for (int i=0; i<v.size();i++){
      cout << v[i] << " : ";
    }
    cout << endl;
}

void parse_input(int argc, char* argv[])
{
	for(int i=1; i<argc; i++)
	{
		if(string(argv[i]) == string("--meta_file"))
		{
			METADATA_FILEPATH = strdup(argv[i+1]);
		}
		else if(argv[i] == string("--input_file"))
			INPUT_FILEPATH = strdup(argv[i+1]);
		else if(argv[i] == string("--output_file"))
			OUTPUT_FILEPATH = strdup(argv[i+1]);
		else if(argv[i] == string("--mm"))
		{
			sscanf(argv[i+1], "%lf", &mm);
			mm *= 1024*1024*0.8;
		}
		else if(argv[i] == string("--output_column"))
		{
            char *c1 = strtok(argv[i+1], ",");
			while(c1 != NULL)
			{
                out_cols.pb(stoi(c1+3));
				// comp_cols.add_sort_column(c1);
				c1 = strtok(NULL, ",");
			}
		}
		else if(argv[i] == string("--sort_column"))
		{
			char *c1 = strtok(argv[i+1], ",");
			while(c1 != NULL)
			{
                comp_cols.pb(stoi(c1+3));
				// comp_cols.add_sort_column(c1);
				c1 = strtok(NULL, ",");
			}
		}
		else if(argv[i] == string("--order"))
		{
			if(argv[i+1] == string("asc"))
				order = 0;
			else
				order = 1;
		}
	}
   // trace(mm);
	/*
	trace(metadata);
	trace(input);
	trace(output);
	trace(mm);
	trace(order);
	cout<<"sort_order : ";
	for(auto i: Metadata::sort_order)
		cout<<i<<" ";
	cout<<endl;
	cout<<"print_order : ";
	for(auto i: Metadata::print_order)
		cout<<i<<" ";
	cout<<endl;
	*/
}



void twoWayMs(CSVMetaData csv_metadata)
{
    // phase 1
    CSVRelation inputdata = CSVRelation(INPUT_FILEPATH);
    Relation r1 = Relation(&inputdata, &metadata);
   // printV(metadata);
    //trace(r1.num_rows_in_file);
    //trace(csv_metadata.size);
    if((mm*mm) /csv_metadata.size < r1.num_rows_in_file * csv_metadata.size)
        cout << "not enough RAM!" << endl;
    //trace(r1.num_rows_in_file * csv_metadata.size);// << endl;
    ll size_of_input_file = r1.num_rows_in_file * csv_metadata.size;
    int num_sorted_sub_lists = (int)ceil(size_of_input_file/mm);
    int rows_per_rel = r1.num_rows_in_file/num_sorted_sub_lists;
    int max_rows_per_file = (int)(mm/csv_metadata.size);
    //trace(num_sorted_sub_lists);
    //trace(rows_per_rel);
    //trace(max_rows_per_file);
    ifstream input_file(INPUT_FILEPATH);
    string temp_prefix = "/tmp/two_way_MS";
    for (int sub_list = 0; sub_list < num_sorted_sub_lists; sub_list++) {
        string file_name = temp_prefix+to_string(sub_list);
        ofstream tmpFile(file_name, ofstream::out);
        r1.readRows(input_file,max_rows_per_file);
        r1.sort(order);
        r1.print(tmpFile);
        // r1.print();
        tmpFile.close();
        r1.clearRows();
      //  cout << "-----" <<endl;
    }
    cout << "completed phase 1" << endl;
    // phase 2
    int max_rows_per_buffer = max_rows_per_file/(2*num_sorted_sub_lists);
    int max_rows_output_buffer = max_rows_per_file - num_sorted_sub_lists*max_rows_per_buffer;
    //trace(max_rows_per_buffer);
    //trace(max_rows_output_buffer);
    vector<pair<Relation, int> > sorted_sub_lists;
    vector<CSVRelation> sorted_csvs;
    vector<ifstream * > files;
    for (int sub_list = 0; sub_list < num_sorted_sub_lists; sub_list++) {
        string file_name = temp_prefix+to_string(sub_list);
        sorted_csvs.pb(CSVRelation(file_name));
        sorted_sub_lists.pb(make_pair(Relation(&(sorted_csvs[sub_list]),&metadata),sub_list));
        ifstream * sub_file = new ifstream(file_name);
        sorted_sub_lists[sub_list].first.readRows(*sub_file,max_rows_per_buffer);
        files.pb(sub_file);
        // sub_file.close();
        //cout << "-----" <<endl;
    }
    // sorted_sub_lists[0].first.print();
    typedef pair<Row, int> row_int_pair;
    ofstream outputFile(OUTPUT_FILEPATH, ofstream::out);
    CSVRelation outputCSV = CSVRelation(OUTPUT_FILEPATH);
    Relation output_rel(&outputCSV,&metadata);
    priority_queue<row_int_pair, vector<row_int_pair>, function<bool(row_int_pair,row_int_pair)> > q;
    if(order)
        q = priority_queue<row_int_pair, vector<row_int_pair>,
            function<bool(row_int_pair,row_int_pair)> >(less<row_int_pair>());
    else
        q = priority_queue<row_int_pair, vector<row_int_pair>,
            function<bool(row_int_pair,row_int_pair)> >(greater<row_int_pair>());
    vector<int> completedTill;
    for (int sub_list = 0; sub_list < num_sorted_sub_lists; sub_list++) {
        completedTill.pb(0);
        // sorted_sub_lists[sub_list].first.rows[0].print();
        q.push(make_pair(sorted_sub_lists[sub_list].first.rows[0],sorted_sub_lists[sub_list].second));
    }
    int co = 0;
    row_int_pair temp_pair;
    int count1 = 0;
    while(!q.empty())
    {
        temp_pair = q.top();
        q.pop();
        output_rel.rows.pb(temp_pair.first);
        // temp_pair.first.print();
        // cout << count1++ << " " << q.size() << " " << sorted_sub_lists.size() << endl;
        int sub_list = temp_pair.second;
        int row_num = completedTill[sub_list];
        if(sorted_sub_lists[sub_list].first.rows.size()-1 > row_num)
        {
            q.push(make_pair(sorted_sub_lists[sub_list].first.rows[++row_num],sub_list));
            completedTill[sub_list]++;
        }
        else
        {
            sorted_sub_lists[sub_list].first.clearRows();
            sorted_sub_lists[sub_list].first.readRows(*files[sub_list],max_rows_per_buffer);
            // cout << sub_list << " readRows" << endl;
            if(sorted_sub_lists[sub_list].first.rows.size() == 0)
            {
                // cout << "deleting sub_list " << sub_list << endl;
                num_sorted_sub_lists--;
                if(num_sorted_sub_lists == 0)
                    max_rows_per_buffer = max_rows_per_file;
                else
                    max_rows_per_buffer = max_rows_per_file/(2*num_sorted_sub_lists);
                // max_rows_output_buffer = max_rows_per_file - num_sorted_sub_lists*max_rows_per_buffer;
            }
            else
            {
                // cout << "refilling " << sub_list << endl;
                completedTill[sub_list] = 0;
                q.push(make_pair(sorted_sub_lists[sub_list].first.rows[0],sorted_sub_lists[sub_list].second));
            }
            // cout << "breaking" << endl;
            // break;
        }
        if(output_rel.rows.size() >= max_rows_output_buffer)
        {
            // cout << "filling output" << endl;
            co += output_rel.rows.size();
            // cout << output_rel.rows.size() << endl;
            output_rel.printCols(outputFile);
            output_rel.clearRows();
        }
    }
    // cout << "filling output" << endl;
    co += output_rel.rows.size();
    // cout << output_rel.rows.size() << endl;
    output_rel.printCols(outputFile);
    output_rel.clearRows();
//    cout << co << endl;
    // cout << "out le loop" << endl;
    outputFile.close();
    cout << "completed phase 2" << endl;
}

int main(int argc, char* argv[])
{
    parse_input(argc,argv);
//    printVs(comp_cols);
    CSVMetaData csv_metadata = CSVMetaData(METADATA_FILEPATH);
    metadata = csv_metadata.getMetaData();
    metadata_map = csv_metadata.getMetaDataMap();
    //printV(metadata);
    //printVs(metadata_map);
    twoWayMs(csv_metadata);
    // cout << r1.rows.size();
    // r1.print();
    return 0;
}
