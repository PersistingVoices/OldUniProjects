#include<iostream>
using namespace std;

class Footballer
{
        protected:
                string name, club;
                int games, goals_scored, assists, clean_sheets, goals_conceded;

        public:
                void setValues (string nm, string cb, int gms, int gls, int asts) 
                {
                    name = nm; club = cb; 
                    games = gms; goals_scored = gls; 
                    assists = asts;
                }

        string getName() {return name;}
        string getClub() {return club;}
        int getGames() {return games;}
        int getGoalsScored() {return goals_scored;}
        int getAssists() {return assists;}

        virtual void CleanSheets() {cout<< clean_sheets;}
        virtual void GoalsConceded() {cout<< goals_conceded;}
};


class Defender: public Footballer
{
        protected:
                int clean_sheets, goals_conceded;

        public:
                void setValues (string nm, string cb, int gms, int gls, int asts, int clnshts, int glscon) 
                {
                    name = nm; club = cb; 
                    games = gms; goals_scored = gls; 
                    assists = asts; clean_sheets = clnshts; 
                    goals_conceded = glscon;
                }
                
                void CleanSheets() {cout<<"Clean_Sheet::Defender:"<< clean_sheets<<endl;}
                void GoalsConceded() {cout<<"Goals_Conceded::Defender:"<< goals_conceded<<endl;}
};

class Goalkeeper: public Footballer
{
        protected:
                int clean_sheets, goals_conceded, saves;
        public:
                void setValues (string nm, string cb, int gms, int gls, int asts, 
                                int clnshts, int glscon, int saves)
                {
                        name = nm; club = cb;
                        games = gms; goals_scored = gls;
                        assists = asts; clean_sheets = clnshts; 
                        goals_conceded = glscon; saves=saves;
                };
                void CleanSheets() {cout<<"Clean_Sheet::Goalkeeper:"<< clean_sheets<<endl;}
                void GoalsConceded() {cout<<"Goals_Conceded::Goalkeeper:"<< goals_conceded<<endl;}
};

void print_all_for(Footballer *F)
{
    F->CleanSheets();
    F->GoalsConceded();
}


int main() {

        Footballer *PeterCrouch = new Footballer ; 
        PeterCrouch->setValues("Peter Crouch", "Stoke City", 31, 7, 3) ;

        cout<<endl;

        Defender *GarethMcAuley = new Defender ; 
        GarethMcAuley->setValues("Gareth McAuley", "West Bromwich Albion", 22, 0, 0, 11, 27) ;
        //GarethMcAuley->CleanSheets(); // this can be uncommented to check for individual values
        print_all_for(GarethMcAuley);
    
        cout<<endl;

        Goalkeeper *SomeBloke   = new Goalkeeper; 
        SomeBloke->setValues("Some Bloke", "Somehere", 22, 0, 0, 15, 27, 9) ;
        //SomeBloke->CleanSheets(); // this can be uncommented to check for individual values
        print_all_for(SomeBloke);
        
        cout<<endl;
        return 0;
}
