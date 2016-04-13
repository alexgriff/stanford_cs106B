/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

bool isEnoughHospitals(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               Vector< Set<string> >& locationsToTry,
                               int numHospitals,
                               Vector< Set<string> >& result);



int main() {
    string A, B, C, D, E, F;
    A = "A"; B = "B"; C = "C"; D = "D"; E = "E"; F = "F";
    
    Set<string> cities;
    cities += A, B, C, D, E, F;
    
    
    Set<string> loc1, loc2, loc3, loc4;
    loc1 += A, C, D;
    loc2 += A, B, C;
    loc3 += B, F;
    loc4 += C, E, F;
    
    Vector< Set<string> > locations;
    locations += loc1, loc2, loc3, loc4;
    
    Vector< Set<string> > result;
    
    int counter = 1;
    if (canOfferUniversalCoverage(cities, locations, 2, result)){
        cout << "true" << endl << endl;
        foreach(Set<string> hospitalCoverage in result) {
            cout << "Hospital " << counter << " covers: " << hospitalCoverage <<endl;
            counter++;
        }
    }
    else cout << "false" << endl << endl;
    
    cout << "---------------------------------" << endl;
    
    counter = 1;
    if (canOfferUniversalCoverage(cities, locations, 3, result)){
        cout << "true" << endl << endl;
        foreach(Set<string> hospitalCoverage in result) {
            cout << "Hospital " << counter << " covers: " << hospitalCoverage <<endl;
            counter++;
        }
    }
    else cout << "false" << endl << endl;

    return 0;
}








bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result)
{
    /* BETTER RECURSIVE BACKTRACKING WAY...
    if(cities.size() == 0) return true;
	else if(numHospitals == 0) return false;
	else{
		for(int i = 0; i < locations.size(); i++){
			Set<string> citiesLeftToCover = cities;
            foreach (string city in locations[i]) citiesLeftToCover.remove(city);
			result.add(locations[i]); 
			if(canOfferUniversalCoverage(citiesLeftToCover, locations, numHospitals - 1, result)) return true;
            result.remove(result.size() - 1);
        } 
	}
	return false; */
    
    Vector< Set<string> > locationsToTry;
    return isEnoughHospitals(cities, locations, locationsToTry, numHospitals, result);
    
}

bool isEnoughHospitals(Set<string>& cities,
                       Vector< Set<string> >& locations,
                       Vector< Set<string> >& locationsToTry,
                       int numHospitals,
                       Vector< Set<string> >& result)
{
    
    /* Some exceptional cases */
    if (cities.size() == 0) {
        return true;
    } else if (numHospitals == 0) {
        return false;
    
    /* BASE CASE: no locations left in list.  Go through your proposed locations and add up the cities
       covered by this set, return if all cities are present */
    } else if (locations.size() == 0) {
        Set<string> coveredCities;
        
        for (int i = 0; i < locationsToTry.size(); i++) {
            if (i < numHospitals) {
                result.add(locationsToTry[i]);
                foreach(string city in locationsToTry[i]) {
                    coveredCities.add(city);
                }
            }
        }
        return (cities.isSubsetOf(coveredCities));
    
    } else {
        
        result.clear();
        
        /* For each potential hospital location: can choose to add it to the list
         for proposed construction, or choose to skip that location and not build it */
        
        Vector< Set<string> > proposed = locationsToTry;
        proposed += locations[0];
        Vector< Set<string> > remaining = locations;
        remaining.remove(0);
        if (isEnoughHospitals(cities, remaining, proposed, numHospitals, result)) return true;
        
        proposed = locationsToTry;
        if (isEnoughHospitals(cities, remaining, proposed, numHospitals, result)) return true;
        
        
        
    }
    return false;
}









