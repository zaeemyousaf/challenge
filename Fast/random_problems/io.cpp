// reading and writing to a file
#include <iostream>
using namespace std;

class FileIO
{
public:
  FileIO();
    void save(String fileName, dataStructure graph)
    {
	try 
	    {
		FileOutputStream fileOutput;
		ObjectOutputStream objectStr;

		fileOutput = new FileOutputStream(fileName);
		objectStr = new ObjectOutputStream(fileOutput);
		objectStr.writeObject(graph);			
		fileOutput.close();
			
	    }
	catch (Exception e)		
	    {
		cout <<(e);
			
	    }
		
    }
	
    public dataStructure load(String fileName) throws IllegalArgumentException
    {
		
		dataStructure newTree = null;
	try
	    {
		FileInputStream fileOutput;
		ObjectInputStream objectStr;


		fileOutput = new FileInputStream(fileName);
		objectStr = new ObjectInputStream(fileOutput);
			
		newTree = (dataStructure)objectStr.readObject();
			
		fileOutput.close();
		cout << "is it working";
	    }
		
	catch (ClassNotFoundException ex)		
	    {
		cout <<(ex);
	    }
		
	catch (Exception e)
	    {
		cout <<(e);
	    }
	return newTree;
    }
    
};
