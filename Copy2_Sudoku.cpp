#include<iostream>
#include<math.h>
#include<time.h>
using namespace std;

class Sudoku
{
public:
    static int seed;
    int dim;
    int mat[10][10];

    Sudoku(int d)
    {
        dim = d;
        initialize_matrix( );
    }
    void initialize_matrix( ) //Initializes matrix dim x dim with all 0s
    {
         for( int i=0; i<dim; i++)
        {
            for( int j=0; j<dim; j++)
            {
                mat[i][j] = 0;
            }
        }
    }

    void enter_mat() //Enter elements of matrix
    {
        for( int i=0; i<dim; i++)
        {
            for( int j=0; j<dim; j++)
            {
                cout<<"["<<i<<"]["<<j<<"]: ";
                cin>>mat[i][j];
            }
        }
    }

    void print_mat() //Print elements of matrix
    {
        cout<<endl;

        for(int i=0; i<dim; i++)
        {
            for(int j=0; j<dim; j++)
            {
                cout<<mat[i][j]<<" ";
            }

            cout<<endl;
        }
        cout<<endl;
    }

    bool check_row_col(int this_row, int this_col) //Check if element can be in row and column
    {
        bool XOR(bool,bool);

        for( int i=0; i<dim; i++)
        {
            for( int j=0; j<dim; j++)
            {
                if ( (XOR(i == this_row , j == this_col)) and mat[i][j] == mat[this_row][this_col] )
                {
                    return 0;
                }
            }
        }

        return 1;
    }

    int start_index(int index) //Finds starting index for checking box
    {
        int start_index = index;

        while( start_index % dim != 0)
        {
            start_index--;
        }

        return start_index;
    }

    bool check_box(int this_row , int this_col) //Checks if element can be in box
    {
        int row = start_index(this_row);
        int col = start_index(this_col);

        //cout<<"box-row "<<row<<" box-col "<<col<<endl;

        for( int i=0; i<dim; i++)
        {
            for( int j=0; j<dim; j++)
            {
                if ( ( row+i != this_row || col+j != this_col ) && ( mat[row+i][col+j]  ==  mat[this_row][this_col] ) )
                {
                    return 0;
                }

            }
        }

        return 1;
    }

    bool check_pos( int this_row , int this_col) //Checks if element can be in certain position in matrix
    {
        if( check_row_col(this_row , this_col))
        {
            cout<<"PASS ROW COL"<<endl;
            if( check_box(this_row , this_col))
            {
                cout<<"PASS BOX"<<endl;
                return 1;
            }
        }
        cout<<"FAILED"<<endl;
        return 0;
    }

    bool Sud_Pos( int coor0, int coor1)
    {
        int options[dim];
        int new_coor[2];
        void next_coor(int,int[]);

        if( Sud_Complete())
        {
            return 1;
        }

        Shuffle_Option(options);

        for( int i=0; i<dim; i++)
        {
            mat[ coor0 ][ coor1 ] = options[i];

            print_mat();
            //cout<<coor0<<" "<<coor1<<" "<<mat[coor0][coor1]<<" "<<options[i]<<endl;

            if( check_pos(coor0,coor1) )
            {
                //cout<<"HIHIHI"<<endl;
                new_coor[0] = coor0;
                new_coor[1] = coor1;

                next_coor( dim, new_coor );
                //cout<<new_coor[0]<<" "<<new_coor[1]<<endl;

                if ( Sud_Pos( new_coor[0] , new_coor[1] ) )
                {
                    return 1;
                }
            }

        }

        mat[ coor0 ][ coor1 ] = 0;
        return 0;
    }

    void Generate_Sudoku()
    {
        if( Sud_Pos( 0,0 ) )
        {
            cout<<"GENERATED SUDOKU: "<<endl;
            print_mat();
        }
        else
        {
            cout<<"FAILED SUDOKU: "<<endl;
            print_mat();
        }
    }

    void Shuffle_Option(int arr[])
    {
        bool same;

        srand(seed);
        seed++;

        for(int i=0;i<dim;i++)
        {
            do{
                same=false;
                int randm= rand()%dim+1; //generate random number
                arr[i]=randm;
                for(int check=0;check<i;check++)
                {
                    if(arr[i]==arr[check])
                    {
                        same=true;
                        break;
                    }
                }
            }while(same);
        }
    }

    bool Sud_Complete()
    {
        for(int i=0; i<dim; i++)
        {
            for( int j=0; j<dim; j++)
            {
                if (mat[i][j] == 0)
                {
                    return 0;
                }
            }
        }

        return 1;
    }

    static int get_seed()
    {
        cout<<"Enter seed: ";
        cin>>seed;

        return seed;
    }

};


bool XOR( bool x , bool y) //XOR logic gate
{
    if (x != y)
    {
        return 1;
    }

    return 0;
}

bool AND( bool x , bool y) //AND logic gate
{
    if( x==1 && y==1)
    {
        return 1;
    }
    return 0;
}

void next_coor( int dim , int pos[] )
{

    if ( pos[1] == dim-1 )
    {
        pos[0]++;
        pos[1] = 0;
    }
    else
    {
        pos[1]++;
    }

}

int Sudoku::seed = get_seed();

int main()
{
    int arr[4];
    Sudoku S(4);
    int pos[2] = {0,0};

    S.Generate_Sudoku();

}
