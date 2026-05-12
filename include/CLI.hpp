#pragma once

#include <iostream>
#include <string>

#include"CommitHandler.hpp"
#include"FileSystem.hpp"
#include"Utils.hpp"
#include "DatabaseManager.hpp"
using namespace std;

namespace CLI {
    DatabaseManager db(".mgit/minigit.db");

    void printHelp(){
        cout<<"\n minigit- A Simple Version Control System \n";
        cout<<"Commands:\n";
        cout<<"minigit init     -initialize a new repository\n";
        cout<<"minigit commit -m\"msg\" -save a snapshot of your files\n";
        cout<<"minigit log      -view commit history\n";
        cout<<"minigit restore <id>    -restore files from a commit\n"; 
        cout<<"minigit help     -show this menu\n";
        cout<<"\n";
    }
    void run(int argc,char*argv[]){
        if(argc < 2){
            cout<<"No command provided.\n";
            printHelp();
            return;
        }
         string command = argv[1];

         if(command =="init"){
            FileSystem::initialize_folders(); 
            CommitHandler::handleInit(db); 
            cout<<"intialized empty minigit repository.\n";
         }
         else if(command == "commit"){

            if(argc < 4){
                cout<<"Error: commit requires a messsage. \n";
                cout<<"How to use: minigit commit -m\"your message\"\n";
                return;
            }   
        string flag  = argv[2];
        if (flag!="-m"){
            cout<<"Error unknown flag"<<flag<<endl;
            cout<<"How to use: minigit commit -m\"your message\"\n";
            return;
        }

        string message = argv[3];
        string commitID = Utils::generate_alphanumeric(8);
        FileSystem::snapshot(commitID);      
        CommitHandler::Commit commit;
        commit.id        = commitID;
        commit.message   = message;
        commit.author    = "Unknown";
        commit.timestamp = Utils::get_db_iso_string(); 
        
        CommitResponse result = CommitHandler::handleCommit(db, commit);

            if(result.success){
                cout<<"Snapshot saved. Commit ID: "<<commitID<<"\n";
            }else{
                cout<<"Error: "<<result.message<<"\n";
            }
         }else if(command=="log"){
           
          CommitHandler::handleLog(db); 
       
        }else if(command=="restore"){ 

            if(argc < 3){
                cout<<"Error: restore requires a commit ID.\n";
                cout<<"How to use: minigit restore <commitID>\n";
                return;
            } 
        string commitID = argv[2];

        CommitHandler::Commit found;
            if(!CommitHandler::fetchCommitById(db, commitID, found)){
                cout<<"Error: commit ID '"<<commitID<<"' not found.\n";
                return;
            }
        
        FileSystem::restore(commitID);
            cout<<"Restored files from commit: "<<commitID<<"\n";

        
        }else if(command == "help"){ 
        printHelp();

       }else{
        cout<<"Unknown Command!"<<command<<"\n";
        printHelp();
       } 
    
    }
   
}