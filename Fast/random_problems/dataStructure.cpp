
class dataStructure{
private:
    LinkList vertices = null;

    dataStructure(){
      this.vertices = new LinkList();
    }

    void makeVertex(String label){
        if(!isVertex(label,this.vertices)){
            dataStructureVertex vertex = new dataStructureVertex(label);
            this.vertices.insertLast(vertex);
        }

    }


    public void makeVertex(String label, Object value){
        if(!isVertex(label,this.vertices)){
            dataStructureVertex vertex = new dataStructureVertex(label, value);
            this.vertices.insertLast(vertex);
        }
    }


    void connectEdge(String label1, String label2){
        Scanner sc = new Scanner(System.in);
        if(isVertex(label1,this.vertices) && isVertex(label2,this.vertices)){
            dataStructureVertex v1 = getVertex(label1);
            dataStructureVertex v2 = getVertex(label2);
            if(!isVertex(v2.getLabel(), v1.getAdjacent())){
                v1.connectEdge(v2);
            }

            if(!isVertex(v1.getLabel(), v2.getAdjacent())){
                v2.connectEdge(v1);
            }


        }
    }

     bool isVertex(String label, LinkList vertexList){
        bool check = false;
        Iterator iter = vertexList.iterator();
        dataStructureVertex iterElement = null;
        while(iter.hasNext()){
            iterElement = (dataStructureVertex)iter.next();
            if(iterElement.getLabel().equals(label)){
                check = true;
            }
        }
        return check;
    }


    public dataStructureVertex getVertex(String label){
        Iterator iter = this.vertices.iterator();
        dataStructureVertex vertexElement = null;
        dataStructureVertex expectedVertex = null;
        while (iter.hasNext()) {
            vertexElement = (dataStructureVertex)iter.next();
            if(vertexElement.getLabel().equals(label)){
                expectedVertex = vertexElement;
            }
        }
        return expectedVertex;
    }


    public LinkList getAdjacent(String label){
        LinkList vertexList = null;
        if(isVertex(label,this.vertices)){
            vertexList = getVertex(label).getAdjacent();
        }
        else{
            cout <<("Vertex of such label name is absent!!!");
        }
        return vertexList;
    }


    public bool isAdjacent(String label1, String label2){
        bool check = false;
        dataStructureVertex vertexElement = null;
        if(isVertex(label1,this.vertices) && isVertex(label2,this.vertices)){
            Iterator iter = getAdjacent(label1).iterator();
            while(iter.hasNext()){
                vertexElement = (dataStructureVertex)iter.next();
                if(vertexElement.getLabel().equals(label2)){
                    check = true;
                }
            }
        }
        else{
        }
        return check;
    }

    LinkList getAllVertex(){
	return vertices;
    }


     void print(){
        Iterator iterVertex = this.vertices.iterator();
        dataStructureVertex vertexElement = null;
        dataStructureVertex vertexEdges = null;
        cout <<("\nPrint  normally  with vertex and edges");
        while(iterVertex.hasNext()){
            vertexElement = (dataStructureVertex)iterVertex.next();
	    cout << "is it working...";
	}

     void printAssetSummary(){
	int totalAssets = 0;
	
        Iterator iterVertex = this.vertices.iterator();
        dataStructureVertex vertexElement = null;
        dataStructureVertex vertexEdges = null;
        cout <<("\nPrint  normally  with vertex and edges");
        while(iterVertex.hasNext()){
            vertexElement = (dataStructureVertex)iterVertex.next();
	    cout <<(vertexElement.getLabel() + ": ");
	    int edgeCounter = 0;
            Iterator iterVertexEdgesList = vertexElement.getAdjacent().iterator();
	    totalAssets++;
            while(iterVertexEdgesList.hasNext()){
                vertexEdges = (dataStructureVertex)iterVertexEdgesList.next();
		edgeCounter++;
	    }
	    cout <<("value: "+ edgeCounter);
        }

	cout << "is it working...";
    }

};
