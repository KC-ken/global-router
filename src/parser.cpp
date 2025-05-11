#include "parser.h"

int numNet=0;

void glob :: parser( int argc, char **argv )
{
    //check argument count
    if( argc != 3 )
    {
        cout << "Usage: ./mono <input_file_name> <output_file_name>" << endl;
        exit(1);
    }

    fstream fin;
    fin.open(argv[1], fstream::in);

    //check argument open
    if( !fin.is_open() )
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    char buffer[100];

    //parser start
    while( !fin.eof() )
    {
        fin >> buffer;
        if( !strcmp(buffer,"grid") )
        {
            //input number of horizontal tiles
            fin >> buffer;
            hori = atoi(buffer);
            //input number of vertical tiles
            fin >> buffer;
            vert = atoi(buffer);
        }
        if( !strcmp(buffer,"capacity") )
        {
            //input capacity of tile
            fin >> buffer;
            capacity = atoi(buffer);
        }
        if( !strcmp(buffer, "num") )
        {
    		fin >> buffer;
    		fin >> buffer;
        	int size = atoi(buffer);
        	nets.resize( size );
        	
        	for( int i = 0 ; i < size ; ++i )
            {
                //input non default x1 y1 x2 y2 cost
                fin >> buffer;
                nets[i].setID( atoi(buffer) );
                fin >> buffer;
                nets[i].setXs( atoi(buffer) );
                fin >> buffer;
                nets[i].setYs( atoi(buffer) );
                fin >> buffer;
                nets[i].setXt( atoi(buffer) );
                fin >> buffer;
                nets[i].setYt( atoi(buffer) );
            }
		}
    }

    fin.close();
    
    // The following demonstrates how to use the parser
	cout << "grid " << hori << " " << vert << endl; 
	cout << "capacity " << capacity << endl;
	cout << "num net " << nets.size() << endl; 
	for( int i = 0 ; i < nets.size() ; ++i )
	{
	cout << nets[i].getID() << " " << nets[i].getXs() << " "
				<< nets[i].getYs() << " " << nets[i].getXt()	<< " " 
				<< nets[i].getYt() << " " << endl;
	}

    return;
}


bool operator<(Path p1, Path p2)
{
    return p1.getCost() > p2.getCost();
}

void glob::output(int argc, char** argv)
{
    std::ofstream fout(argv[2]);
    if (!fout.is_open()) {
        std::cerr << "Error: cannot open output file!" << std::endl;
        exit(1);
    }

    std::vector<std::vector<Pcost>> Pcosts(hori, std::vector<Pcost>(vert));
    std::vector<std::vector<Path>> path(hori, std::vector<Path>(vert));
    std::priority_queue<Path> mypq;
    std::stack<int> outStack;

    // Initialize path coordinates and base cost
    for (int i = 0; i < hori; ++i) {
        for (int j = 0; j < vert; ++j) {
            path[i][j].setX(i);
            path[i][j].setY(j);
            Pcosts[i][j].setRight(1.0 / capacity);
            Pcosts[i][j].setUp(1.0 / capacity);
        }
    }

    for (int netID = 0; netID < nets.size(); ++netID) {
        // Reset path data
        for (int i = 0; i < hori; ++i) {
            for (int j = 0; j < vert; ++j) {
                path[i][j].setPi(0);
                path[i][j].setCost(std::numeric_limits<float>::max());
            }
        }

        int xs = nets[netID].getXs(), ys = nets[netID].getYs();
        int xt = nets[netID].getXt(), yt = nets[netID].getYt();
        int X, Y;

        path[xs][ys].setCost(0);
        mypq.push(path[xs][ys]);

        // Dijkstra's algorithm with cost checking
        while (!mypq.empty()) {
            float refCost;
            bool found = false;

            do {
                if (mypq.empty()) break;
                Path current = mypq.top();
                mypq.pop();
                X = current.getX(); Y = current.getY();
                refCost = current.getCost();
            } while (refCost != path[X][Y].getCost());

            if (refCost != path[X][Y].getCost()) break;

            if (Y < vert - 1 && path[X][Y].getCost() + Pcosts[X][Y].getUp() < path[X][Y + 1].getCost()) {
                path[X][Y + 1].setCost(path[X][Y].getCost() + Pcosts[X][Y].getUp());
                path[X][Y + 1].setPi(3);
                mypq.push(path[X][Y + 1]);
            }

            if (X < hori - 1 && path[X][Y].getCost() + Pcosts[X][Y].getRight() < path[X + 1][Y].getCost()) {
                path[X + 1][Y].setCost(path[X][Y].getCost() + Pcosts[X][Y].getRight());
                path[X + 1][Y].setPi(4);
                mypq.push(path[X + 1][Y]);
            }

            if (Y > 0 && path[X][Y].getCost() + Pcosts[X][Y - 1].getUp() < path[X][Y - 1].getCost()) {
                path[X][Y - 1].setCost(path[X][Y].getCost() + Pcosts[X][Y - 1].getUp());
                path[X][Y - 1].setPi(1);
                mypq.push(path[X][Y - 1]);
            }

            if (X > 0 && path[X][Y].getCost() + Pcosts[X - 1][Y].getRight() < path[X - 1][Y].getCost()) {
                path[X - 1][Y].setCost(path[X][Y].getCost() + Pcosts[X - 1][Y].getRight());
                path[X - 1][Y].setPi(2);
                mypq.push(path[X - 1][Y]);
            }
        }

        // Backtrack path
        X = xt; Y = yt;
        outStack.push(Y); outStack.push(X);

        while (X != xs || Y != ys) {
            switch (path[X][Y].getPi()) {
				case 1:
					Pcosts[X][Y].setUp(Pcosts[X][Y].getUp() + (1.0 / capacity) + (Pcosts[X][Y].getUp() >= 1.0) * 10000);
					++Y;
					break;
				case 2:
					Pcosts[X][Y].setRight(Pcosts[X][Y].getRight() + (1.0 / capacity) + (Pcosts[X][Y].getRight() >= 1.0) * 10000);
					++X;
					break;
				case 3:
					Pcosts[X][Y - 1].setUp(Pcosts[X][Y - 1].getUp() + (1.0 / capacity) + (Pcosts[X][Y - 1].getUp() >= 1.0) * 10000);
					--Y;
					break;
				case 4:
					Pcosts[X - 1][Y].setRight(Pcosts[X - 1][Y].getRight() + (1.0 / capacity) + (Pcosts[X - 1][Y].getRight() >= 1.0) * 10000);
					--X;
					break;
			}
            outStack.push(Y);
            outStack.push(X);
        }

        // Write to output
        fout << netID << " " << (outStack.size() / 2 - 1) << std::endl;
        fout << outStack.top(); outStack.pop();
        fout << " " << outStack.top(); outStack.pop();

        while (outStack.size() > 2) {
            int outX = outStack.top(); outStack.pop();
            int outY = outStack.top(); outStack.pop();
            fout << std::endl << outX << " " << outY;
            fout << std::endl << outX << " " << outY;
        }

        fout << " " << outStack.top(); outStack.pop();
        fout << " " << outStack.top(); outStack.pop() << std::endl;
    }

    fout.close();
}


