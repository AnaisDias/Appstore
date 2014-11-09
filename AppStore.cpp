/*
 * AppStore.cpp
 *
 *  Created on: 18 de Out de 2014
 *      Author: Sofia
 */

#include <string>
#include "AppStore.h"
#include "Exceptions.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

AppStore::AppStore() {
	this->name = "APP STORE";
}

AppStore::AppStore(string name) {
	this->name = name;
}

AppStore::~AppStore() {
	for(unsigned int i=0; i<clients.size(); i++){
		delete clients[i];
		clients.erase(clients.begin()+i);
		i--;
	}
	for(unsigned int i=0; i<developers.size(); i++){
		delete developers[i];
		developers.erase(developers.begin()+i);
		i--;
	}
	for(unsigned int i=0; i<transactions.size(); i++){
		delete transactions[i];
		transactions.erase(transactions.begin()+i);
		i--;
	}
}

void AppStore::addApp(App* app) {
	apps.push_back(app);
}
void AppStore::addClient(Client* cli) {
	clients.push_back(cli);
}
void AppStore::addDeveloper(Developer* dev) {
	developers.push_back(dev);
}

// Saves AND Loads

//Menus

//Gets e Sets

string AppStore::getName() {
	return name;
}
void AppStore::setName(string name) {
	this->name = name;
}

vector<App*> AppStore::getApps() {
	return apps;
}
void AppStore::setApps(vector<App*> apps) {
	this->apps = apps;
}

vector<Client*> AppStore::getClients() {
	return clients;
}
void AppStore::setClients(vector<Client*> clients) {
	this->clients = clients;
}

vector<Developer*> AppStore::getDevelopers() {
	return developers;
}

void AppStore::setDevelopers(vector<Developer*> developers) {
	this->developers = developers;
}

vector<Transaction*> AppStore::getTransactions()
{
	return transactions;
}

void AppStore::setTransactions(vector<Transaction *> transactions)
{
	this->transactions = transactions;
}

bool AppStore::removeApp(App* app) {
	for (unsigned int i = 0; i < apps.size(); i++) {
		if (apps[i] == app)
			apps.erase(apps.begin()+i);
			i--;
			return true;
	}
	return false;
}

App* AppStore::findAppByID(int id){
	for(unsigned int i=0; i<apps.size();i++){
		if(apps[i]->getID()==id) return apps[i];
	}
	throw AppDoesNotExist(id);
	return NULL;
}

vector<App*> AppStore::findAppsByName(string name){
	vector<App*> appsbyname;
	for(unsigned int i=0; i<apps.size();i++){
		if(apps[i]->getName()==name) appsbyname.push_back(apps[i]);
	}
	return appsbyname;
}

vector<App*> AppStore::findAppsByType(int type){
	vector<App*> appsbytype;
	for(unsigned int i=0; i<apps.size();i++){
		if(apps[i]->getType()==type) appsbytype.push_back(apps[i]);
	}
	return appsbytype;
}

bool ordenaRating(App* app1, App* app2){
	return (app1->getRatings() > app2->getRatings());
}

vector<App*> AppStore::orderAppsByTop5Rating(){
	vector<App*> apps2 = apps;
	vector<App*> top5;
	sort(apps2.begin(), apps2.end(), ordenaRating);
	for(int i=0; i<5; i++){
		top5.push_back(apps2[i]);
	}
	return top5;
}



Client* AppStore::findClientByID(int id){
	for(unsigned int i=0; i<clients.size();i++){
		if(clients[i]->getID()==id) return clients[i];
	}
	throw ClientDoesNotExist(id);
	return NULL;
}

Developer* AppStore::findDeveloperByID(int id){
	for(unsigned int i=0; i<developers.size();i++){
		if(developers[i]->getID()==id) return developers[i];
	}
	throw DeveloperDoesNotExist(id);
	return NULL;
}

Transaction* AppStore::findTransactionByID(int id){
	for(unsigned int i=0; i<transactions.size();i++){
		if(transactions[i]->getID()==id) return transactions[i];
	}
	throw TransactionDoesNotExist(id);
	return NULL;
}

//////////MENUS//////////

/////////////////////////
////////SUB APP /////////
/////////////////////////

void AppStore::Top5Apps(){
	vector<App*> top5 = orderAppsByTop5Rating();
	char input;
	cout << "TOP 5 APPS" << endl << endl;
	for(int i=0; i<top5.size(); i++){
		cout << top5[i] << endl;
	}
	cout << endl << "Select app by ID or enter 'r' to return: ";
	cin >> input;
	int in = input - '0';
	if(input == 'r') return;
	else try{
		AppManagementMenu(findAppByID(in));
	}
	catch (AppDoesNotExist &e1){
		cout << "Specified app does not exist. ID: " << e1.getID() << endl;
	}
}

void AppStore::AppsListName() {
	string input;
	char input2;
	vector<App*> appsN;
	cout << "Enter app name: ";
	cin >> input;
	appsN=findAppsByName(input);

	system("cls");
	cout << "Apps List By NAME: " << endl;
	if(appsN.empty()) {
		cout << "No apps with the requested name. Press any key to go back" <<endl;
		cin.get();
		return;
	}
	else{
		for(int i=0; i<appsN.size();i++){
			cout << appsN[i] << endl;
		}
	}

	cout << endl << "Select app by ID or enter 'r' to return: ";
	cin >> input2;
	int in = input2 - '0';
	if(input2 == 'r') {
		system("cls");
		return;
	}
	else try{
		AppManagementMenu(findAppByID(in));
	}
	catch (AppDoesNotExist &e1){
		cout << "Specified app does not exist. ID: " << e1.getID() << endl;
	}
}


void AppStore::AppsListType() {
	int type;
	char input;
	vector<App*> appstype;
	cout << "Apps List By TYPE: " << endl;
	cout << endl << "Types: ";
	cout << "1. Entertainment" << endl;
	cout << "2. Finances" << endl;
	cout << "3. Games" << endl;
	cout << "4. Fitness" << endl;
	cout << "5. Lifestyle" << endl;
	cout << "6. Music" << endl;
	cout << "7. Photography" << endl;
	cout << "8. Productivity" << endl;
	cout << "9. Social Networks" << endl;
	cout << "10. Sports" << endl;
	cout << "11. Traveling" << endl;
	cout << "12. Utilities" << endl;

	cout << "Select a type: ";
	cin >> type;
	appstype = findAppsByType(type);
	if(appstype.empty()){
		cout << "No apps with the requested type. Press any key to go back" <<endl;
		cin.get();
		return;
	}
	else{
	for(int i=0; i<appstype.size(); i++){
		cout << appstype[i]->displayInfo() << endl;
	}
	}

	cout << endl << "Select app by ID or enter 'r' to return: ";
	cin >> input;
	int in = input - '0';
	if(input == 'r') {
		system("cls");
		return;
	}

	else try{
		AppManagementMenu(findAppByID(in));
	}
	catch (AppDoesNotExist &e1){
		cout << "Specified app does not exist. ID: " << e1.getID() << endl;
	}
	//insert try and catch here

}

void AppStore::AllAppsList(){
	char input;
	if(apps.empty()){
		cout << "No apps. Press any key to go back" <<endl;
		cin.get();
		return;
	}
	vector<App *>::iterator it = apps.begin();
	for( ;it<apps.end(); it++){
		cout << (*(*it)).displayInfo();
				cout << endl;
	}
	cout << endl << "Select app by ID or enter 'r' to return: ";
	int in = input - '0';
	if(input == 'r') {
		system("cls");
		return;
	}

	else try{
		AppManagementMenu(findAppByID(in));
	}
	catch (AppDoesNotExist &e1){
		cout << "Specified app does not exist. ID: " << e1.getID() << endl;
	}
}
void AppStore::RateApps() {
	string name;
	char y = 'y';
	int rate;
	char input;

	cout << "Which app do you want to rate?" << endl;
	cout << "Apps List:" << endl;

	if(apps.empty()){
		cout << "No apps. Press any key to go back" <<endl;
		cin.get();
		return;
	}
	for(int i=0; i<apps.size(); i++){
		 cout << apps[i]->displayInfo();
				 cout << endl;
	}
	cout << endl << "Select app by ID or enter 'r' to return: ";
	cin >> input;
	int in= input - '0';
	if(input == 'r') {
		system("cls");
		return;
	}

	else{
	system("cls");
	cout << "RATE:" << endl;
	cout << "1 - Hate" << endl;
	cout << "2 - Dislike" << endl;
	cout << "3 - Like" << endl;
	cout << "4 - Love" << endl;
	cout << "5 - Amazing" << endl;
	cout << "0 - Go Back" << endl;
	cout << "OPTION: ";
	cin >> rate;

		try{
			App *app = findAppByID(in);
			app->addRating(rate);
			cout << "Rating added successfully!" << endl;
		}
		catch (AppDoesNotExist &e1){
			cout << "Specified app does not exist. ID: " << e1.getID() << endl;
		}

	}
}

void AppStore::AddApplicationMenu() {
	string name, desc;
	int price, type, dev;
	cout << "ADD APP" <<endl;
	cout << "Insert the following information: " << endl << endl;
	cout << "Name: ";
	cin >> name;
	cout << endl << "Price: ";
	cin >> price;
	cout << endl << "Type (select from 1 to 12): ";
	cin >> type;
	cout << endl << "Add a short description (no commas): ";
	cin >> desc;
	cout << endl << "Developer's ID: ";
	cin >> dev;

	App *app;
	app = new App(name, price, type, desc);
	app->setDeveloper(findDeveloperByID(dev));
	//add try and catch exception here

	addApp(app);

	cout << "App" << name << "Added Successfully To The Appstore" << endl;
	cout << endl;
	cout << "Press any key to return ";
	cin.get();

}


void AppStore::RemoveApplicationMenu() {
	char input;
	if(apps.empty()){
		cout << "No apps. Press any key to go back" <<endl;
		cin.get();
		return;
	}
	for(int i=0; i<apps.size(); i++){
		cout << apps[i] << endl;
	}
	cout << endl << "Select app by ID or enter 'r' to return: ";
	cin >> input;
	if(input == 'r') {
		system("cls");
		return;
	}

	App *app = findAppByID((int)input);
	// add try and catch here;
	removeApp(app);

	cout << "App removed successfully from the Appstore" << endl;
	cout << endl;
	cout << "Press any key to return ";
	cin.get();
}

void AppStore::AppManagementMenu(App* app){

	string name;
	int choice, type, dev, rating;
	system("cls");
	cout << "APP MANAGEMENT: ID=" << app->getID() << endl << endl;
	cout << "What do you wish to do? " << endl;
	cout << "1. Change name" << endl;
	cout << "2. Change type" << endl;
	cout << "3. Change developer" << endl;
	cout << "4. Add rating" << endl;
	cout << "5. Remove app" << endl;
	cin >> choice;
	//change name
	//change developer
	//change type
	//add rating
	//remove app

	switch(choice) {

			case 1: system("cls");
			cout << "Insert new name ";
					cin >> name;
					app->setName(name);
					cout << endl << "Name changed to " << name << endl;
					break;
			case 2: "Insert new type ";
			cin >> type;
			app->setType(type);
			cout << endl << "Type changed to " << type << endl;
					break;
			case 3: "Insert new developer ID ";
			cin >> dev;
			app->setDeveloper(findDeveloperByID(dev));
			//add try and catch here
			cout << endl << "Developer's new ID is " << dev << endl;

					break;
			case 4: "Insert new rating ";
			cin >> rating;
			app->addRating(rating);
			cout << endl << "Rating added: " << rating << endl;

					break;
			case 5: removeApp(app);
					cout << "App successfully removed. ";
					break;
			default: break;
	}
	cout << endl;
	cout << "Press any key to return ";
	cin.get();
}

/////////////////////////
//////SUB CLIENT ////////
/////////////////////////

void AppStore::ClientsList() {
	cout << "CLIENTS LIST" << endl;
	//display list

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if(y == 'y') {
	system("cls");
	ClientMenu();
	}
}

void AppStore::PurchasedApps() {
	cout << "PURCHASED APPS" << endl;
	//display list

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		ClientMenu();}
}

void AppStore::AddClients() {
	string name;
	cout << "Name Of The Client To Be Added: ";
	cin >> name;

	//add client

	cout << "Client Added Successfully To The Appstore Database" << endl;

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		ClientMenu();
	}
}

void AppStore::RemoveClients() {
	string name;
	cout << "Name Of The Client To Be Removed: ";
	cin >> name;

	//remove client

	cout << "Client Removed Successfully From The Appstore Database" << endl;

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		ClientMenu();
	}

}

/////////////////////////
//////SUB DEV ///////////
/////////////////////////

void AppStore::IndividualDevList() {
	cout << "INDIVIDUAL DEVELOPERS: " << endl;

	//display list

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		DeveloperMenu();
	}


}

void AppStore::EnterpriseList() {
	cout << "ENTERPRISES: " << endl;

	//display list

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		DeveloperMenu();
	}


}

void AppStore::AppsCreated() {
	int choice;
	char y = 'y';
	string name;
	cout << "APPS CREATED BY A DEV/ENTERPRISE: " << endl;
	cout << "1 - Individual Developer" << endl;
	cout << "2 - Enterprise" << endl;
	cout << "0 - Go back" << endl;
	cout << "OPTION: ";
	cin >> choice;

	switch(choice) {

	case 1: system("cls");
			//display list of devs
			cout << endl;
			cout << "Apps Created By: ";
			cin >> name;
			//display apps;
			cout << endl;
			cout << "Go Back? (y)";
			cin >> y;
			if (y == 'y') {
				system("cls");
				DeveloperMenu();
			}
			break;
	case 2: system("cls");
			//display list of enterprises
			cout << endl;
			cout << "Apps Created By: ";
			cin >> name;
			//display apps;
			cout << endl;
			cout << "Go Back? (y)";
			cin >> y;
			if (y == 'y') {
				system("cls");
				DeveloperMenu();
			}
			break;
	case 0: system("cls");
			DeveloperMenu();
			break;
	default: break;
	}
}

void AppStore::SalesData() {

}

void AppStore::AddDev() {
	string name;
	cout << "Developer To Be Added: ";
	cin >> name;

	//add dev to the appstore

	cout << "Developer Added Successfully To The Appstore" << endl;

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		DeveloperMenu();
	}
}

void AppStore::RemoveDev() {
	string name;
	cout << "Developer To Be Removed: ";
	// display list of Devs
	cout << "Remove: ";
	cin >> name;

	//remove dev from the appstore

	cout << "Developer Removed Successfully From The Appstore" << endl;

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		DeveloperMenu();
	}
}

/////////////////////////
//////SUB TRANS /////////
/////////////////////////

void AppStore::TransApps() {
	cout << "APPS TRANSACTIONS: " << endl;
	//display apps transactions

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		TransactionMenu();
	}
}

void AppStore::TransClients() {
	cout << "CLIENTS TRANSACTIONS: " << endl;
	//display the client transactions????

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		TransactionMenu();
	}
}

void AppStore::TransDev() {
	cout << "DEVELOPERS/ENTERPRISES TRANSACTIONS: " << endl;
	//display the devs list and which transaction the client wants to see????? lol

	cout << endl;
	char y = 'y';
	cout << "Go Back? (y)";
	cin >> y;
	if (y == 'y') {
		system("cls");
		TransactionMenu();
	}
}

/**********************************************************
 *                    SAVES AND LOADS                     *
 *********************************************************/

void AppStore::saveApps()
{
	vector<App *>::iterator it = apps.begin();

	ofstream file;
	file.open("apps.txt", ios::trunc);


	for(; it != apps.end(); it++)
	{
		(*it)->writeToFile(file);
		file << endl;
	}

	system("cls");
	file.close();
	cout << "\n Apps saved." << endl;
}

void AppStore::saveDevelopers()
{
	vector<Developer *>::iterator it = developers.begin();

	ofstream file;
	file.open("developers.txt",ios::trunc);

	for(; it != developers.end(); it++)
	{
		(*it)->writeToFile(file);
		file << endl;
	}
	system("cls");
	file.close();
	cout << "\n Developers saved." << endl;
}

void AppStore::saveClients()
{
	vector<Client *>::iterator it = clients.begin();

	ofstream file;
	file.open("clients.txt",ios::trunc);

	for(; it != clients.end(); it++)
	{
		(*it)->writeToFile(file);
		file << endl;
	}
	system("cls");
	file.close();
	cout << "\n Clients saved." << endl;
}

void AppStore::saveTransactions()
{
	vector<Transaction *>::iterator it = transactions.begin();

	ofstream file;
	file.open("transactions.txt",ios::trunc);

	for(; it != transactions.end(); it++)
	{
		(*it)->writeToFile(file);
		file << endl;
	}
	system("cls");
	file.close();
	cout << "\n Transactions saved." << endl;
}


