#include <iostream>
#include<string>
//#include <list>
#include <algorithm>// replace_if
//#include <sstream> // for Printint Point Function in Point Class 
//#include<utility>
#include <vector>
//#include <chrono>//std::this_thread::sleep_for(std::chrono::milliseconds(x));
#include <thread>//^
#include <io.h>  //for wcout
#include <fcntl.h>//^
#include"SFML\Graphics.hpp"
using namespace std;
const int width = 800, height = 600;
char wantToDisplayWhileProcessing, seeAllpaths;
bool firstTime = true;
bool logging = false;
const int dd = -1;// -->** The Default Value For Points
//typedef vector<Point>::const_iterator c_it;
struct Point
{
public:
	int x = 0, y = 0, NUM = 0;
	float H = 0, G = 0, F = 0;
	int  ParentX = 0, ParentY = 0;// Or Point Parent; 
	int State = 0;
	bool Checked = false;
	//bool existInOpenList = false;
	Point()
	{}
	Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	bool operator == (Point P)
	{
		return (this->x == P.x && this->y == P.y);
	}
	bool operator != (Point P)
	{
		return !(this->x == P.x && this->y == P.y);
	}
	Point In(vector<Point> List)
	{
		for (Point P : List)
		{
			if (this->x == P.x && this->y == P.y)
			{
				return P;
			}

		}
		return Point(-1, -1);
	}


};





vector<Point> points;
vector<Point>openList;
vector<Point>closedList;
vector<Point>ThePath;
std::vector<sf::RectangleShape> blocks;
std::vector<sf::RectangleShape> path;
std::vector<sf::RectangleShape> LifePath;
vector<Point>blocksInt;
Point TheCurrentRegion;
vector<Point> ConvertShapeToPoint(std::vector<sf::RectangleShape> bb)
{
	vector<Point> temp;
	for (auto X : bb)
	{
		temp.push_back(Point(X.getPosition().x, X.getPosition().y));
	}
	return temp;
}

class AStar
{

private:



public:

	bool reachTheEnd = false;
	float G = 0;

	static bool Equal(Point X, Point P)
	{
		return (X.x == P.x && X.y == P.y);
	}
	static bool NotEqual(Point X, Point P)
	{
		return !(X.x == P.x && X.y == P.y);
	}
	/*Point ConvertParentToPoint(Point MyPoint)
	{
		int x = 0, y = 0;

		x = MyPoint.Parent %width - 1;
		y = ((MyPoint.Parent - (x + 1)) / width);
		Point t;
		t.x = x;
		t.y = y;
		return(t);
	}*/

	Point PointOffset(int x, int y, Point Main, vector<Point> Map)
	{
		Point temp;
		int offX, offY;
		int indexOfPoint;
		offX = Main.x + x;
		offY = Main.y + y;
		indexOfPoint = (offY * width) + offX;
		//temp = Map.at(indexOfPoint);
		return Point(offX, offY);
	}
	/*	Point ConvertParentToPointInMap(Point ToConvert,vector<Point> Map)
		{
			int x = 0, y = 0;

			for (Point Pt : Map)
			{
				if (Equal(ToConvert , Pt))
				{

					//Parent =
					x = Pt.Parent %width - 1;
					y = ((Pt.Parent - (x + 1)) / width);
					Point t;
					t.x = x;
					t.y = y;
					return CollectPointDataFromTheMap(t, Map);
				}
			}

		}*/


	void UpdatePoint(vector<Point>& Map, Point Old, Point P/*, int Mode = 1, char WantToMoveIt = 'N'*/)
	{
		vector<Point>::iterator it = find(Map.begin(), Map.end(), Old);
		//for (vector<Point>::iterator it = Map.begin(); it != Map.end(); ++it)
		{
			//	if (Old.x == it->x&&Old.y == it->y)
			{



				//if (it != Map.end())   // 1

				{
					//	*it = P;
					it->H = P.H;
					it->G = P.G;
					it->F = P.F;
					it->ParentX = P.ParentX;
					it->ParentY = P.ParentY;
					it->NUM = P.NUM;
					it->State = P.State;
					it->Checked = P.Checked;
					//	return;
				}

				//Map.insert(it, P);
				//points.insert(it, P);
				//replace(Map.begin(), Map.end(), temp,P);
				//replace


			}

		}
	}
	bool Contain(Point P, vector<Point> Map)
	{
		for (Point x : Map)
			if (P == x)
				return true;

		return false;
	}

	void SettingData(Point offset, Point End, char d = 'n')
	{
		bool newPath = false;
		//vector<Point>::iterator indexx;
		//indexx = openList.begin();
		//int indexNum = 0;
		Point temp;
		temp = offset;
		// tentative_gScore is the distance from start to the neighbor through current
		//tentative_gScore: = gScore[current] + d(current, neighbor)
			//temp.Parent = TheCurrentRegion.NUM;
		float addition;
		/*if (d != 'n')
			addition =  (1 * 1);
		else
			addition = (sqrt(2) * 1);
		*/
		if (d != 'n')
			addition = (10 * 1);
		else
			addition = (14 * 1);

		G = TheCurrentRegion.G + addition;
		//vector<Point>::iterator it2 = openList.begin();
		//it2 = find(openList.begin(), openList.end(), temp);
		//vector<Point>::iterator it = find(openList.begin(), openList.end(), temp);
		//if (it== openList.end())   // 1
		/*{temp.ParentX = TheCurrentRegion.x;
		temp.ParentY = TheCurrentRegion.y;
			temp.H = GetDistance(temp, End, 'Z');

			if (d != 'n')
				temp.G =( TheCurrentRegion.G)+(1*1);
			else
				temp.G = TheCurrentRegion.G + (sqrt(2)*1);

			temp.F = temp.G + temp.H;

		//	temp.existInOpenList = true;
			openList.push_back(temp);
			//openList.at(tempIndex).existInOpenList = true;
		//	int index = (temp.y*width) + temp.x;
//			points.at(index) = temp;
		}*/
		Point neighbor = temp.In(openList);

		if (neighbor != Point(-1, -1))   // 1  it== openList.end()
		{
			if (TheCurrentRegion.G + addition < neighbor.G)
			{
				Point tt = TheCurrentRegion;
				neighbor.ParentX = TheCurrentRegion.x;
				neighbor.ParentY = TheCurrentRegion.y;
				neighbor.G = TheCurrentRegion.G + addition;
				neighbor.F = TheCurrentRegion.F;

				//Point newPoint = temp;
				//newPoint.G = G;
				//newPoint.Checked = false;

				UpdatePoint(openList, neighbor, neighbor);
				//newPath = true;

			}
			//else

		}
		else
		{
			/*if (d != 'n')
				temp.G = (TheCurrentRegion.G) + (1 * 1);
			else
				temp.G = TheCurrentRegion.G + (sqrt(2) * 1);
			*/
			if (d != 'n')
				temp.G = (TheCurrentRegion.G) + (10 * 1);
			else
				temp.G = TheCurrentRegion.G + (14 * 1);

			//temp.G ;
			//newPath = true;
			temp.ParentX = TheCurrentRegion.x;
			temp.ParentY = TheCurrentRegion.y;
			temp.H = GetDistance(temp, End, 'X');
			temp.F = temp.G + temp.H;
			openList.push_back(temp);
		}

		/*if (newPath)
		{
			temp.ParentX = TheCurrentRegion.x;
			temp.ParentY = TheCurrentRegion.y;
			temp.H = GetDistance(temp, End, 'Z');


			temp.F = temp.G + temp.H;
			UpdatePoint(openList, temp, temp);
			//	temp.existInOpenList = true;
			//openList.push_back(temp);
		}
	*/

	/*vector<Point>::iterator it2 = find(closedList.begin(), closedList.end(), temp);
	if (it2 != closedList.end())
	{
	/*	temp.ParentX = TheCurrentRegion.x;
		temp.ParentY = TheCurrentRegion.y;

		temp.G = (TheCurrentRegion.G + (GetDistance(TheCurrentRegion, *it2, 'k', 1)));
		temp.F = it2->G + it2->H;

		closedList.erase(it2);
		closedList.push_back(temp);

	}
*/
/*			float dist = GetDistance(TheCurrentRegion, *it2) ;
			if ((TheCurrentRegion.G + (GetDistance(TheCurrentRegion,*it2, 'k', 1))) < it2->G)
			{

				it2->ParentX = TheCurrentRegion.x;
				it2->ParentY = TheCurrentRegion.y;

				it2->G = (TheCurrentRegion.G + (GetDistance(TheCurrentRegion, *it2, 'k', 1)));
				it2->F = it2->G + it2->H;
				it2->Checked = false;
				//if (Contain(temp,closedList))
					//UpdatePoint(closedList, *it, *it);
				//it->Checked = false;
		//		UnChecked();


			}*/


	}
	void LoadingNeighboursInOpenList(Point currentRegion, Point& Start, Point End)
	{
		if (firstTime)
		{
			//	Start.NUM = ((Start.y*width) + Start.x)+1;
				//Start.UpdatePoint(closedList, Start);
			Start.H = GetDistance(TheCurrentRegion, End, 'X');
			Start.F = TheCurrentRegion.H;
			TheCurrentRegion = Start;
			TheCurrentRegion.H = GetDistance(TheCurrentRegion, End, 'X');
			TheCurrentRegion.F = TheCurrentRegion.H;
			firstTime = false;
			//openList.push_back(Start);
		}
		//------------------------------------------------------------------------
		for (int x = -10; x <= 10; x += 10)
		{
			for (int y = -10; y <= 10; y += 10)
			{
				Point tt = PointOffset(x, y, TheCurrentRegion, points);
				//vector<Point>::iterator it = find(blocksInt.begin(), blocksInt.end(), tt);

				if (!Contain(tt, blocksInt) && tt.x >= 0 && tt.x <= width && tt.y >= 0 && tt.y <= height)
				{
					if (x == 0 && y == 0)
					{
					}
					else {

						if (x == 0 || y == 0)
							SettingData(tt, End, 'm');
						else
							SettingData(tt, End, 'n');
					}
				}
				else
				{

				}
			}
		}
	}

	void UnChecked()
	{
		for (Point& x : openList)
		{
			if (x.Checked)
				x.Checked = false;
		}
	}

	bool SolveThePath(Point Start, Point End)
	{
		float smallestF;
		Point temp = Point(-1, -1);
		vector<Point>::iterator it2;
		int counterx = 0;
		int checking_rate = 1000;
		int Last_Check = 0;
		while (!reachTheEnd && openList.size() != 0)
		{
			it2 = openList.begin();
			temp = Point(-1, -1);
			//Point temp = GetTheNearestPoint(openList, TheCurrentRegion,Start, End);// 25r temp hwa el = el (End point)
			smallestF = -1;
			LoadingNeighboursInOpenList(TheCurrentRegion, Start, End);
			bool pushInClosedList = true;
			int counter = 0, tempIndex = 0;
			if (logging)
				cout << "***************************** OpenList Before Chosing **********************************\n";


			for (vector<Point>::iterator it = openList.begin(); it != openList.end(); ++it)
			{
				if (logging)
					cout << " Open ~" << counter << "~ :  ( " << it->x << ", " << it->y << " )\nG Value : " << it->G << "\nF Value : " << it->F << "\n Parent (" << it->ParentX << " ," << it->ParentY << ") \n";

				if (!it->Checked)
				{
					if (smallestF == -1)//To Be Applied In The First Time To Start The Comparison With The Other Points'2
					{
						smallestF = it->F;
						temp = *it;
						it2 = it;
						tempIndex = counter;
					}

					if (it->F > 0)

						if (smallestF > it->F)// pt.F <= smallestF
						{
							smallestF = it->F;
							if (*it != TheCurrentRegion && *it != Start)
								temp = *it;
							it2 = it;
							tempIndex = counter;
						}

					//pushInClosedList = true;
				}

				counter++;
				//else
					//pushInClosedList = false;
			}
			if (temp != TheCurrentRegion)
				TheCurrentRegion = temp;
			//else
				//openList.erase(it2);
			//if (logging)



		/*
			int i = 0;

			for (Point &it : openList)
			{

				if (!it.Checked)
				{
					if (smallestF == -1)//To Be Applied In The First Time To Start The Comparison With The Other Points'2
					{
						smallestF = it.F;
						temp = it;
						int x = 0;

						advance(it2, x);
					}

					if (it.F > 0)

						if (smallestF > it.F)// pt.F <= smallestF
						{
							smallestF = it.F;
							temp = it;
							int x = i - 1;
							advance(it2,i);

						}
					i++;

				}
			}
		*/
		//	int indexx = (temp.y *width) + temp.x;
		//	points.at(indexx).Checked = true;
			//points.at(indexx).existInOpenList = false;
		//it2 = openList.begin();
		//advance(it2, tempIndex);







			if (logging)
			{
				cout << " *************************************************************End\n";
				cout << " The Current :  ( " << TheCurrentRegion.x << ", " << TheCurrentRegion.y << " )\nG Value : " << TheCurrentRegion.G << "\nF Value : " << TheCurrentRegion.F << "\nParent (" << TheCurrentRegion.ParentX << ", " << TheCurrentRegion.ParentY << ") \n";

			}

			if (!Contain(TheCurrentRegion, closedList))//||temp.Checked==false
			{
				if (logging)
				{
					cout << "*Point ( " << TheCurrentRegion.x << ", " << TheCurrentRegion.y << " ) Has Been Removed From OpenList \n\n";
					cout << "*Point ( " << TheCurrentRegion.x << ", " << TheCurrentRegion.y << " ) Has Been Accepted \n";
				}
				closedList.push_back(temp);

				//Point p;
				openList.erase(it2);
				//			if (logging)


			}
			else
			{
				openList.at(tempIndex).Checked = true;
			}
			/*if (false)
			{
			cout << "\n\n***************************** OpenList In Case Of Erasing **************************************\n";
			int counterz = 0;


				for (Point In : openList)
				{
					cout << " Open [" << counterz << "] (" << In.x << ", " << In.y << " )\nG Value : " << In.G << "\nF Value : " << In.F << "\n";
					counterz++;
				}

				cout << " *************************************************************End\n";
			}*/
			//openList.erase(openList.begin() + tempIndex);
					//openList.at(tempIndex).Checked = true;
			if (Equal(TheCurrentRegion, End))
			{
				reachTheEnd = true;

				UpdateTheMainMap(points, closedList, End, Start, temp, 'n', 'dw');
			}





			if (counterx > Last_Check + checking_rate)
			{
				if (openList.size() == 0)
				{
					return false;
				}
				Last_Check = counter;
			}
			counterx++;

			/*for (Point x : closedList)
			{
				sf::RectangleShape rect;
				rect.setSize({ 10,10 });
				rect.setFillColor(sf::Color::Green);
				rect.setPosition(x.x, x.y);
				rect.setOutlineColor(sf::Color::Black);
				rect.setOutlineThickness(1);
				LifePath.push_back(rect);
			}*/

		}
		//UpdateTheMainMap(points, closedList, End, Start, temp,'z', 'x');
		//	system("pause");
			//system("cls");
		//	Mymap.ClearMap(points);

		return true;
	}

	/*	Point GetTheNearestPoint(vector<Point>Map,Point CurrentPlace,Point Start,Point End)
		{

			float smallestF = -1;
			Point temp = Point(0,0);
			vector<Point>::iterator it2;

		for(vector<Point>::iterator it = openList.begin();it!=openList.end();++it)
		{
			LoadingNeighboursInOpenList(TheCurrentRegion, Start, End);

					if (smallestF ==-1)//To Be Applied In The First Time To Start The Comparison With The Other Points'2
					{
						smallestF = it->F;
						temp = *it;
						it2 = it;
					}

					if (it->F > 0)

						if (smallestF > it->F/*||pt.F<=TheCurrentRegion.F)// pt.F <= smallestF
						{
							smallestF = it->F;
							temp = *it;
							it2 = it;
						}
		}


	openList.erase(it2);

	if (!temp.Checked)
	{
		closedList.push_back(temp);
	}
	temp.Checked = true;
	TheCurrentRegion = temp;
	return temp;

	}*/
	void UpdateTheMainMap(vector<Point>& MainMap, vector<Point>NewMap, Point End, Point Start, Point tempPoint, char ShowAllPaths = 'n', char ShowTheProcess = 'n')
	{
		Point N;
		Point temp2;
		temp2 = TheCurrentRegion;
		if (ShowAllPaths == 'n')
		{

			while (NotEqual(N, Start))
			{
				if (NotEqual(temp2, Start))
				{
					N = Point(temp2.ParentX, temp2.ParentY);
					for (Point d : closedList)
						if (d == N)
							N = d;
					Point P = Point(N.x, N.y);

					if (Equal(N, Start))
					{

					}
					else if (NotEqual(N, Start))
					{
						ThePath.push_back(P);
					}
					temp2 = N;

				}

				else
				{
					break;
				}
			}
		}
		/*
		else if (ShowAllPaths == 'yL')//Live
		{

			for (Point &P : MainMap)
			{
				for (Point & N : NewMap)
				{
					Point tempPoint = N;
					if (Equal(P , tempPoint))
					{
						if (tempPoint.x > (tempPoint).ParentX || (tempPoint.x - End.x == -1 && tempPoint.y == End.y))
							P.State = 6;
						else if (tempPoint.x < (tempPoint).ParentX || (tempPoint.x - End.x == 1 && tempPoint.y == End.y))
						{
							P.State = 4;
						}
						if (P.State != 0)
						{
							if (tempPoint.y > (tempPoint).y || (tempPoint.ParentY - End.y == -1 && tempPoint.x == End.x))

								P.State = 2;
							else if (tempPoint.y < (tempPoint).ParentY || (tempPoint.y - End.y == 1 && tempPoint.x == End.x))
								P.State = 8;
						}
						else
							P.State = 9;
						if ((tempPoint.x - End.x == -1 && tempPoint.y == End.y))
							P.State = 6;
						else if ((tempPoint.x - End.x == 1 && tempPoint.y == End.y))
							P.State = 4;
						else if ((tempPoint.y - End.y == -1 && tempPoint.x == End.x))
							P.State = 2;
						else if ((tempPoint.y - End.y == 1 && tempPoint.x == End.x))
							P.State = 8;
					}
					//P.State = 9;
				}
			}
		}*/
		/*	else if (ShowAllPaths == 'y')
			{

				for (Point &P : MainMap)
				{


						if (Equal(P , tempPoint))
						{
							if (tempPoint.x > (tempPoint).ParentX || (tempPoint.x - End.x == -1 && tempPoint.y == End.y))
								P.State = 6;
							else if (tempPoint.x < (tempPoint).ParentX || (tempPoint.x - End.x == 1 && tempPoint.y == End.y))
							{
								P.State = 4;
							}
							if (P.State != 0)
							{
								if (tempPoint.y > (tempPoint).y || (tempPoint.ParentY - End.y == -1 && tempPoint.x == End.x))

									P.State = 2;
								else if (tempPoint.y < (tempPoint).ParentY || (tempPoint.y - End.y == 1 && tempPoint.x == End.x))
									P.State = 8;
							}
							else
								P.State = 9;
							if ((tempPoint.x - End.x == -1 && tempPoint.y == End.y))
								P.State = 6;
							else if ((tempPoint.x - End.x == 1 && tempPoint.y == End.y))
								P.State = 4;
							else if ((tempPoint.y - End.y == -1 && tempPoint.x == End.x))
								P.State = 2;
							else if ((tempPoint.y - End.y == 1 && tempPoint.x == End.x))
								P.State = 8;
						}
						//P.State = 9;

				}
			}*/
			/*
				else if(ShowAllPaths=='z')
				{
			//	Mymap.ClearMap(points);
				Point NM;
				Point temp3;
				temp3 = TheCurrentRegion;

				//vector<Point>::iterator iter;

					while (NotEqual(NM , Start))
					{
					//	Mymap.ClearMap(points);
						system("cls");
						NM = Point(temp3.ParentX,temp3.ParentY);
						Point &o = points.at((NM.y*width) + NM.x);
						if (NotEqual(NM, Start))
						{


							if (NM.x > NM.ParentX)
								o.State = 6;
							else if (NM.x < (NM.ParentX))
								o.State = 4;
							if (NM.y > NM.ParentY)
							{
							if (o.State != 0)
								o.State = 2;
							else
								o.State = 9;
							}
							else if (NM.y < NM.ParentY)
							{
								if (o.State != 0)
									o.State = 8;
								else
									o.State = 9;
							}

							if ((NM.x - End.x == -1 && NM.y == End.y))
								o.State = 6;
							else if ((NM.x - End.x == 1 && NM.y == End.y))
								o.State = 4;
							else if ((NM.y - End.y == -1 && NM.x == End.x))
								o.State = 2;
							else if ((NM.y - End.y == 1 && NM.x == End.x))
								o.State = 8;


	temp3 = NM;
	if (ShowTheProcess == 'u')
	{
		for (Point &P : MainMap)
		{

			if (Equal(P, End))
				P.State = 5;
			if (Equal(P, Start))
				P.State = 3;
			if (P.State == 77)
				wcout << L"▲";
			if (P.State == 1)

				wcout << "#";
			//	if(P.State==11)
				//	wcout << "@";
			else if (P.State == 3)
			{


				wcout << "B";
			}
			else if (P.State == 5)
				wcout << "A";
			else if (P.State == 8)
				wcout << L"x";
			else if (P.State == 2)
				wcout << L"x";
			else if (P.State == 4)
				wcout << L"x";
			else if (P.State == 6)
				wcout << L"x";
			else if (P.State == 9)
				wcout << "x";

			else

				wcout << " ";

			if (P.x == (width - 1))
				wcout << "\n";

		}
		Mymap.ClearMap(points);

	}
						}

					}



			}






	*/




	/*if (ShowTheProcess == 'x')
	{
		for (Point &P : MainMap)
		{
			if (Equal(P, End))
				P.State = 5;
			if (Equal(P, Start))
				P.State = 3;
			if(P.State == 77)
				wcout << L"▲";
			if (P.State == 1)

				wcout << "#";
		//	if(P.State==11)
			//	wcout << "@";
			else if (P.State == 3)
			{


				wcout << "A";
			}
			else if (P.State == 5)
				wcout << "B";
			else if (P.State == 8)
				wcout << L"↑";
			else if (P.State == 2)
				wcout << L"↓";
			else if (P.State == 4)
				wcout << L"←";
			else if (P.State == 6)
				wcout << L"→";
			else if (P.State == 9)
				wcout << "*";

			else

				wcout << " ";

			if (P.x == (width - 1))
				wcout << "\n";

		}

	}


	*/

	//this_thread::sleep_for(std::chrono::milliseconds(5));
	//if (NotEqual(TheCurrentRegion , End))
		{
			//if(ShowTheProcess!='u')
			//system("cls");
			//if(ShowAllPaths != 'y'&& ShowAllPaths!='z2')
			//Mymap.ClearMap(points);
		}
	}


	bool CanNotBeSolved(vector<Point>OpenList)
	{
		if (OpenList.size() == 0)
			return true;
	}
	static float GetDistance(Point Start, Point End, char dOru = 'k', int x = 1)//D - > Direct Or U - > Undirect
	{

		if (dOru == 'X')

			return((abs((Start.x - End.x)) + abs((Start.y - End.y))));
		else if (dOru == 'Z')

			return(sqrtf(pow((Start.x - End.x), 2) + pow((Start.y - End.y), 2)));
		else
		{
			if ((abs(Start.x - End.x) + abs(Start.y - End.y)) == 100)
				return 1 * x;
			else
				return sqrtf(2) * x;
		}



	}




};
void restart(AStar& astar, Point StartX, sf::RectangleShape End)
{
	ThePath.clear();
	path.clear();
	openList.clear();
	StartX.H = AStar::GetDistance(StartX, Point(End.getPosition().x, End.getPosition().y), 'Z');
	StartX.F = StartX.H;
	openList.push_back(StartX);
	astar.reachTheEnd = false;
	closedList.clear();
	TheCurrentRegion = StartX;
}

int main()
{

	/*
	_setmode(_fileno(stdout), _O_U16TEXT);
	Map m;
	AStar astar;

		Point End = astar.FindUniquePointByState(5);
	astar.LoadingMap(End);
	Point Start = astar.FindUniquePointByState(3);

	Start.NUM = ((Start.y*width) + Start.x) + 1;
	openList.push_back(Start);
	for (Point & p : points)
	{

		if (p.State == 1)
			wcout << "#";
		else if (p.State == 3)
		{


			wcout << "A";
		}
		else if (p.State == 5)
			wcout << "B";
		else if (p.State == 8)
			wcout << L"↑";
		else if (p.State == 2)
			wcout << L"↓";
		else if (p.State == 4)
			wcout << L"←";
		else if (p.State == 6)
			wcout << L"→";
		else if (p.State == 9)
			wcout << "*";

		else

			wcout << " ";

		if (p.x == (width - 1))
			wcout << "\n";
	}
	wcout << "Do You Want To See The Path Processing ?(y/n)";
	cin >> wantToDisplayWhileProcessing;
	system("cls");



	astar.SolveThePath(Start,End);

	//astar.GetNeighbours(Start);
int i = 0;
	//m.DrawTheMap();

	while (true)
	{

		/*Point *x = new Point();
		x->x = 18;
		x->y = 8;
		x->State = 3;


		//End.UpdatePoint(points, x);
		for (Point & p : points)
		{
			if (AStar::Equal(p , End))
				p.State = 5;
			if (AStar::Equal(p, Start))
				p.State = 3;


			if (p.State == 1)

				wcout << "#";
			else if (p.State == 3)
			{


				wcout << "A";
			}
			else if (p.State == 5)
				wcout << "B";
			else if (p.State == 8)
				wcout << L"↑";
			else if (p.State == 2)
				wcout << L"↓";
			else if (p.State == 4)
				wcout << L"←";
			else if (p.State == 6)
				wcout << L"→";
			else if (p.State == 9)
				wcout << "*";

			else

				wcout << " ";

			if (p.x == (width - 1))
				wcout << "\n";




		}
		system("pause");

		system("cls");
		i++;

	}


	cin.get();
	*/
	AStar astar;
	sf::Image ico = sf::Image();
	
	sf::RenderWindow window(sf::VideoMode(width, height), "A Star Algorithm");
	sf::Vector2f cell_size = sf::Vector2f(10, 10);
	if (ico.loadFromFile("galaxy.png"))
	{
		window.setIcon(ico.getSize().x, ico.getSize().y, ico.getPixelsPtr());
	}
	sf::RectangleShape Start;
	Start.setSize(cell_size);
	Start.setPosition(10, 10);
	Start.setFillColor(sf::Color::Blue);
	sf::RectangleShape End;
	End.setSize(cell_size);
	End.setPosition(50, 60);
	End.setFillColor(sf::Color::Red);
	Point StartX = Point(Start.getPosition().x, Start.getPosition().y);
	StartX.H = AStar::GetDistance(StartX, Point(End.getPosition().x, End.getPosition().y), 'X');
	StartX.F = StartX.H;
	openList.push_back(StartX);
	TheCurrentRegion = StartX;

	//stringstream s;

	//Start.setSize(sf::Vector2f(2, 2));
	//Start.setPosition(1, 1);
	//shape.setPosition(10, 10);
	//shape.setFillColor(sf::Color::Green);
	bool pressToClear = false;
	bool locked = false;
	bool runTheProgram = false;
	sf::Vector2i last_Mouse_pos(0, 0);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) // See "locked" definition
			{
				if (pressToClear)
				{
					ThePath.clear();
					path.clear();
					openList.clear();

					openList.push_back(StartX);
					astar.reachTheEnd = false;
					closedList.clear();
					TheCurrentRegion = StartX;
					pressToClear = false;
				}
				sf::RectangleShape rect;
				rect.setSize(cell_size);
				rect.setPosition(sf::Vector2f(round(sf::Mouse::getPosition(window).x / 10) * 10, round(sf::Mouse::getPosition(window).y / 10) * 10));
				bool wantToRemove = false;
				for (vector<sf::RectangleShape>::iterator it = blocks.begin(); it != blocks.end(); ++it)
				{
					if (rect.getGlobalBounds().intersects(it->getGlobalBounds()))
					{ //if(rect.getPosition().x>b.getPosition().x)
						//rect.move(abs(rect.getPosition().x - b.getPosition().x)*20,0);
						//push = false;
						blocks.erase(it);
						rect.setFillColor(sf::Color::Green);
						wantToRemove = true;
						break;
					}
				}
				if (!wantToRemove)
					locked = true;

			}
			if (event.mouseButton.button == sf::Mouse::Left && event.type == sf::Event::MouseButtonReleased) {


				locked = false;
			}

			if (locked) // See "locked" definition
			{
				sf::RectangleShape rect;
				rect.setSize(cell_size);
				rect.setPosition(sf::Vector2f(round(sf::Mouse::getPosition(window).x / 10) * 10, round(sf::Mouse::getPosition(window).y / 10) * 10));
				sf::Vector2f Pos = sf::Vector2f(round(sf::Mouse::getPosition(window).x / 10) * 10, round(sf::Mouse::getPosition(window).y / 10) * 10);
				Point temp;
				temp.x = Pos.x;
				temp.y = Pos.y;
				bool push = true;
				rect.setFillColor(sf::Color::Yellow);
				for (vector<sf::RectangleShape>::iterator it = blocks.begin(); it != blocks.end(); ++it)
				{
					if (rect.getGlobalBounds().intersects(it->getGlobalBounds()) || rect.getGlobalBounds().intersects(Start.getGlobalBounds()) || rect.getGlobalBounds().intersects(End.getGlobalBounds()))
					{ //if(rect.getPosition().x>b.getPosition().x)
						//rect.move(abs(rect.getPosition().x - b.getPosition().x)*20,0);
						push = false;
						//		 blocks.erase(it);
						rect.setFillColor(sf::Color::Green);

						break;
					}
				}
				if (push)
				{


					blocksInt.push_back(temp);
					blocks.push_back(rect);

				}
			}
			else if (event.type == sf::Event::MouseButtonPressed &&
				event.mouseButton.button == sf::Mouse::Right) {
				blocksInt = ConvertShapeToPoint(blocks);
				Start.setPosition(10, 10);
				if (logging)
				{
					system("cls");

					cout << " Start Point :  ( " << StartX.x << ", " << StartX.y << " )\n\n";
				}
				runTheProgram = true;



			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
				restart(astar, StartX, End);
				sf::Vector2f Pos = sf::Vector2f(round(sf::Mouse::getPosition(window).x / 10) * 10, round(sf::Mouse::getPosition(window).y / 10) * 10);

				End.setPosition(Pos);

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			{
				logging = !logging;
			}
			if (runTheProgram == true)
			{
				if (!astar.SolveThePath(Point(Start.getPosition().x, Start.getPosition().y), Point(End.getPosition().x, End.getPosition().y)))

				{
					cout << "Cannot Be Solved \n";
					system("pause");
					locked = false;
					restart(astar, StartX, End);
				}
				if (astar.reachTheEnd == true)
				{
					pressToClear = true;
					for (Point x : ThePath)
					{
						sf::RectangleShape rect;
						rect.setSize({ 10,10 });
						rect.setFillColor(sf::Color::Green);
						rect.setPosition(x.x, x.y);
						rect.setOutlineColor(sf::Color::Black);
						rect.setOutlineThickness(1);
						path.push_back(rect);
					}
					runTheProgram = false;
				}
			}
		}


		// clear the window with black color
		window.clear();

		//window.clear();

		for (const auto& b : blocks)
			window.draw(b);
		//	for(const auto&l : LifePath)
			//	window.draw(l);

		for (const auto& p : path)
			window.draw(p);

		window.draw(Start);
		window.draw(End);

		window.display();
	}

	return 0;

}
