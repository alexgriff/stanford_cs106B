/*
 * File: InverseGenetics.cpp
 * --------------------------
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "vector.h"
#include "console.h"
using namespace std;

void assembleStrands(string protein, Map<char, Set<string> >& codons, string strand, Set<string>& rnaStrand) {

    if(protein.empty()) {
        rnaStrand.add(strand);
        return;
    }
    
    char aminoAcid = protein[0];
    Set<string> codonSet = codons[aminoAcid];
    
    
    foreach(string codon in codonSet) {
        strand += codon;
        string nextAmino = protein.substr(1);
        assembleStrands(nextAmino, codons, strand, rnaStrand);
        strand.erase(strand.size() - codon.size());
    }
    
}



Set<string> recursivePermutations(string protein, Map<char, Set<string> >& codons) {
    Set<string> rnaStrand;
    
    if (protein.length() == 1)
        return codons[protein[0]];
    
   
    Set<string> codonSet = codons[protein[0]];
    string nextAmino = protein.substr(1);
    Set<string> nextSet = recursivePermutations(nextAmino, codons);
    foreach (string codon in codonSet) {
        foreach(string nextCodon in nextSet) {
            string strand = codon + nextCodon;
            rnaStrand += strand;
        }
    }
    return rnaStrand;
}




/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
Set<string> listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    Set<string> rnaStrand;
    assembleStrands(protein, codons, "", rnaStrand);
    return rnaStrand;
}





/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;
    
    /* The current codon / protein combination. */
    string codon;
    char protein;
    
    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
    
    return result;
}


int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

    Set <string> RNA = listAllRNAStrandsFor("IRL",codons);
    cout << RNA << endl;
    
    
    return 0;
}


