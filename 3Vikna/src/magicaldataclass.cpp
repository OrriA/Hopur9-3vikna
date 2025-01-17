#include <iostream>
#include <vector>
#include <string>
#include "../include/ComputerScientist.h"
#include "../include/FileData.h"
#include "../include/magicaldataclass.h"


/***************************************
 * ToLower; Helper function
 * Takes in a string and returns a lowercase version
 * ***************************************/
string ToLower(string s)
{
    for(unsigned int i = 0; i < s.length(); i++)
    {
        s[i] = tolower(s[i]);
    }
   return s;
}


//Default Constructor
MagicalDataClass::MagicalDataClass()
{
    sortingOption = 1;
    compSortingOption = 1;
}

//Constructor
MagicalDataClass::MagicalDataClass(string filename)
{
    Database = new FileData(filename);
    sortingOption = 1;
    compSortingOption = 1;
}

/*******************************************
 * SetSort()
 * Used to tell the datalayer how the results should be sorted
 * ****************************************/
void MagicalDataClass::SetSort(int option, int mode)
{
    switch(mode)
    {
        case 0:
        {
            if(option < 1)
            {
                option = 1;
            }
            sortingOption = option % 8;
            break;
        }
        case 1:
        {
            if(option < 1)
            {
                option = 1;
            }
            compSortingOption = option % 6;
        }
    }
}

/*******************************************
 * Add()
 * Takes a stringvector, sees if it fits to any datatype,
 * and passes it down to FileData for SQL storage
 * ****************************************/
void MagicalDataClass::Add(vector<string> entry)
{
    for(unsigned int i = 0; i < entry.size(); i++)
    {
        entry[i] += " ";
    }
    if(entry.size() == 8)
    {
         ComputerScientist newEntry(entry[0],entry[1],entry[2],entry[3],entry[4],entry[5],entry[6],entry[7]);
             (*Database).Add(newEntry);
    }
    else if(entry.size() == 5)
    {
        computer newEntry(entry[0],entry[1],entry[2],entry[3]);
            (*Database).Add(newEntry);
    }
}

/************************************************-
 * Sort
 * Returns the passed vector sorted according to the field specified
 * ***********************************************/
vector <ComputerScientist> MagicalDataClass::Sort(vector <ComputerScientist> theList, const int whatField)
{
    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (unsigned int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].field(whatField) < theList[lowestFirst].field(whatField))
                {
                    lowestFirst = i;
                }
            }

        if(lowestFirst != j)
        {
            swap(theList[j], theList[lowestFirst]);
        }
    }
        return theList;
}

/************************************************-
 * Sort
 * Returns the passed vector sorted according to the field specified
 * ***********************************************/
vector <computer> MagicalDataClass::Sort(vector <computer> theList, const int whatField)
{
    int lowestFirst;

    for (unsigned int j = 0; j < theList.size(); j++)
    {
        lowestFirst = j;
        for (unsigned int i = j+1; i < theList.size(); i++)
            {
                if (theList[i].field(whatField) < theList[lowestFirst].field(whatField))
                {
                    lowestFirst = i;
                }
            }

        if(lowestFirst != j)
        {
            swap(theList[j], theList[lowestFirst]);
        }
    }
        return theList;
}

/**********************************************************************************
 * GetAll()
 * Takes inn an (empty) vector of either scientists or computers and populates it
 * Fills in the entire database worth of scientists or comuters
 * *******************************************************************************/
void MagicalDataClass::GetAll(vector<ComputerScientist>& vec)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).DataSet(0);
    vec = stringtoscientist(MyQuery);
    vec = Sort(vec,sortingOption);
}
/***************/
void MagicalDataClass::GetAll(vector<computer>& vect)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).DataSet(1);
    vect = stringtocomputer(MyQuery);
    vect = Sort(vect,compSortingOption);
}

/********************************************************************************
 * Search()
 * Takes in a substring
 * populates a vector with all the computers that fit the term
 * ******************************************************************************/
void MagicalDataClass::Search(vector<computer>& vect, string substring)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).SearchComputers(substring);

    for(unsigned int i = 0; i < MyQuery.size(); i++)
    {
        string info[8];
        for(unsigned int j = 0; j < MyQuery[i].size();j++)
        {
            info[j] = MyQuery[i][j];
        }
        computer compsci(info[1],info[2],info[3],info[4],info[5]);
        vect.push_back(compsci);
    }
    vect = stringtocomputer(MyQuery);
    vect = Sort(vect,compSortingOption);
}

/********************************************************************************
 * Search()
 * Takes in a substring
 * populates a vector with all the scientists that fit the term
 * ******************************************************************************/
void MagicalDataClass::Search(vector<ComputerScientist>& vect, string substring)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).SearchScientists(substring);
    for(unsigned int i = 0; i < MyQuery.size(); i++)
    {
        string info[9];
        for(unsigned int j = 0; j < MyQuery[i].size();j++)
        {
            info[j] = MyQuery[i][j];
        }
        ComputerScientist compsci(info[1],info[2],info[3],info[4],info[5],info[6],info[7],info[8]);
        vect.push_back(compsci);
    }
    vect = stringtoscientist(MyQuery);
    vect = Sort(vect,sortingOption);
}

//****************************************************************************
//StringToScientist(vector< vector<string> >)
//Takes a string matrix and jams it into a vector of computerscientist
//****************************************************************************
vector<ComputerScientist> MagicalDataClass::stringtoscientist(vector<vector<string> > MyQuery)
{
    vector<ComputerScientist> vec;
    for(unsigned int i = 0; i < MyQuery.size(); i++)
    {
        string info[10];
        for(unsigned int j = 0; j < MyQuery[i].size();j++)
        {
            info[j] = MyQuery[i][j];
        }
        ComputerScientist compsci(info[1],info[2],info[3],info[4],info[5],info[6],info[7],info[8]);
        compsci.setFavorite(info[9] == "true");
        vec.push_back(compsci);
    }
    return vec;
}

//****************************************************************************
//StringTocomputer(vector< vector<string> >)
//Takes a string matrix and jams it into a vector of computers
//****************************************************************************
vector<computer> MagicalDataClass::stringtocomputer(vector< vector<string> > vec)
{
    vector<computer> ret;
    for(unsigned int i = 0; i < vec.size(); i++)
    {
        string info[7];
        for(unsigned int j = 0; j < vec[i].size();j++)
        {
            info[j] = vec[i][j];
        }
        computer compsci(info[1],info[2],info[3],info[4],info[5]);
        compsci.setFavorite(info[6] == "true");
        ret.push_back(compsci);
    }
    return ret;
}

/******************************************************************
 * Thin()
 * Takes in a vector and does a standard search
 * removes all entries NOT matching this search
 * ****************************************************************/
void MagicalDataClass::thin(vector<computer>& vec, string term)
{
    vector <computer> foundDudes;
    for (unsigned int i = 0; i < vec.size(); i++)
    {
       string seek = ToLower((vec[i]).OrderedName());
       if(seek.find(ToLower(term)) != std::string::npos)
       {
          foundDudes.push_back(vec[i]);
       }
    }
    vec = foundDudes;
}

/******************************************************************
 * Thin()
 * same as above, but for a vector of scientists instead of computers.
 * ****************************************************************/
void MagicalDataClass::thin(vector<ComputerScientist>& vec, string term)
{
    vector <ComputerScientist> foundDudes;

    for (unsigned int i = 0; i < vec.size(); i++)
    {
       string seek = ToLower((vec[i]).OrderedName());
       if(seek.find(ToLower(term)) != -1)
       {
          foundDudes.push_back(vec[i]);
       }
    }
    vec = foundDudes;
}

/******************************************************************
 * Remove()
 * Takes in a computer or scientist and removes them from the SQL
 * ****************************************************************/
void MagicalDataClass::remove(ComputerScientist vec)
{
    (*Database).RemoveScientists(vec.field(1),vec.field(3));
}

void MagicalDataClass::remove(computer vec)
{
    (*Database).RemoveComputers(vec.field(1));
}

/***********************************************************************
 * addConnection()
 * takes in a pair of scientist and computer and connects them
 * ***********************************************************************/
void MagicalDataClass::AddConnection(ComputerScientist compsci, computer comp)
{
    (*Database).addConnection(compsci,comp);
}

/*************************************************************************
 * getconnection()
 * takes in a scientist or computer
 * returns a vector of all connected computers or vectors
 * **********************************************************************/
vector<ComputerScientist> MagicalDataClass::getConnections(computer comp)
{
    vector<ComputerScientist> results;
   vector< vector<string> > connections;
   connections = (*Database).JoinTables(comp);
   for(unsigned int i = 0; i < connections.size(); i++)
   {
       ComputerScientist smartGuy(connections[i][3],connections[i][4],connections[i][5],connections[i][6],
               connections[i][7], connections[i][8], connections[i][9], connections[i][10]);
       results.push_back(smartGuy);
   }
   results = Sort(results,sortingOption);
   return results;
}

/*************************************************************************
 * getconnection()
 * same as above, but for scientists instead of computers.
 * **********************************************************************/
vector<computer> MagicalDataClass::getConnections(ComputerScientist compsci)
{
    vector<computer> results;
   vector< vector<string> > connections;
   connections = (*Database).JoinTables(compsci);
   for(unsigned int i = 0; i < connections.size(); i++)
   {
       computer smartGuy(connections[i][12],connections[i][13],connections[i][14],
               connections[i][15], connections[i][16]);
       results.push_back(smartGuy);
   }
   results = Sort(results,compSortingOption);
   return results;
}


/***************************************
 * setfavorite()
 * sets the favorite marker
 * *************************************/

void MagicalDataClass::setFavorite(ComputerScientist compsci, bool marker)
{
    Database->update(compsci,9,(marker) ? "true":"false");
}
void MagicalDataClass::setFavorite(computer comp, bool marker)
{
    Database->update(comp,6,(marker) ? "true":"false");
}

/************************************************
 *  GEtfavorite
 * gets every favorite entry
 * **********************************************/
void MagicalDataClass::GetFavorite(vector<ComputerScientist>& vec)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).favorite(0);
    vec = stringtoscientist(MyQuery);
    vec = Sort(vec,compSortingOption);
}

void MagicalDataClass::GetFavorite(vector<computer>& vec)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).favorite(1);
    vec = stringtocomputer(MyQuery);
    vec = Sort(vec,compSortingOption);
}

/******************************************
 * <>Number
 * returns how many <> are in the database
 * **************************************/
int MagicalDataClass::sciNumber()
{
    return (*Database).howManySci();
}

int MagicalDataClass::favSciNumber()
{
    return (*Database).howManyFavSci();
}

int MagicalDataClass::compNumber()
{
    return (*Database).howManyComp();
}

int MagicalDataClass::favCompNumber()
{
    return (*Database).howManyFavComp();
}


void MagicalDataClass::removeConnection(ComputerScientist compsci, computer comp)
{
    (*Database).removeConnection(compsci,comp);
}
/**************************************
 * Update
 * Updates an entry in the SQL
 * Takes in original entry and changed entry
 * **************************************/
void MagicalDataClass::update(ComputerScientist original,ComputerScientist newone)
{
    for(int i = 8; i >= 1; i--)
    {
        (*Database).update(original,i,newone.field(i));
        original.setField(i,newone.field(i));
    }
}

void MagicalDataClass::update(computer original,computer newone)
{
    for(int i = 5; i >= 1; i--)
    {
        (*Database).update(original,i,newone.field(i));
        original.setField(i,newone.field(i));
    }
}

/***********************************************
 * allConnections
 * returns all connected components in the database
 * *********************************************/
void MagicalDataClass::allConnections(vector<computer>& myVector)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).Connections(1);
    myVector = stringtocomputer(MyQuery);
    cout << "size : " << myVector.size();
}

void MagicalDataClass::allConnections(vector<ComputerScientist>& myVector)
{
    vector< vector<string> > MyQuery;
    MyQuery = (*Database).Connections(0);
    myVector = stringtoscientist(MyQuery);
    cout << "size : " << myVector.size();
}
