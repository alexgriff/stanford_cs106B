/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 * This file is my own work.
 */

#include "HuffmanEncoding.h"
#include "pqueue.h"

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	// TODO: Implement this!
    Map<ext_char, int> freqTable;
    ext_char xch;
    
    while ((xch = file.get()) != EOF) {
        freqTable[xch] += 1;
    }
    
    freqTable[PSEUDO_EOF] = 1;
	
	return freqTable;
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
    
    PriorityQueue<Node*> nodesQ = queueUpTrees(frequencies);
    combineTrees(nodesQ);
    
    Node *root = nodesQ.peek();
	return root;
}


PriorityQueue<Node*> queueUpTrees(Map<ext_char, int>& frequencies) {
    PriorityQueue<Node*> nodesQ;
    
    for(ext_char xch :frequencies) {
        Node *node = new Node;
        node->character = xch;
        node->weight = frequencies.get(xch);
        node->zero = NULL;
        node->one = NULL;
        
        nodesQ.enqueue(node, node->weight);
    }

    return nodesQ;
}

void combineTrees(PriorityQueue<Node*>& nodesQ) {
    
    while (nodesQ.size() > 1) {
        Node* zero = nodesQ.dequeue();
        Node* one = nodesQ.dequeue();
        
        Node* interiorNode = new Node;
        interiorNode->character = NOT_A_CHAR;
        interiorNode->weight = (zero->weight + one->weight);
        interiorNode->zero = zero;
        interiorNode->one = one;
        
        nodesQ.enqueue(interiorNode, interiorNode->weight);
    }
}

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	
    if(root != NULL){
		freeTree(root->zero);
		freeTree(root->one);
		delete root;
	}
}


/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
    
    ext_char xch;
    while ((xch = infile.get()) != EOF) {
        Vector<int> encodingSequence;
        if (findSequence(encodingTree, encodingSequence, xch)) {
            for (int i = 0; i < encodingSequence.size(); i++) {
                outfile.writeBit(encodingSequence[i]);
            }
        }
    }
    
    Vector<int> encodingSequence;
    if (findSequence(encodingTree, encodingSequence, PSEUDO_EOF)) {
        for (int i = 0; i < encodingSequence.size(); i++) {
            outfile.writeBit(encodingSequence[i]);
        }
    }
    
 


}

bool findSequence(Node* encodingTree, Vector<int>& sequence, ext_char xch) {
    if (encodingTree->zero == NULL && encodingTree->one == NULL &&
        encodingTree->character == xch) return true;
    else if (encodingTree->zero == NULL && encodingTree->one == NULL &&
             encodingTree->character != xch)
        return false;

    else {
        sequence.add(0);
        if (findSequence(encodingTree->zero, sequence, xch))
            return true;
        sequence.remove(sequence.size()-1);
        
        sequence.add(1);
        if (findSequence(encodingTree->one, sequence, xch))
            return true;
        sequence.remove(sequence.size()-1);
    }
    
    return false;
    
}



/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */

void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
    while (true) {
        ext_char ch = decodeTree(encodingTree, infile);
        if (ch == PSEUDO_EOF) break;
        file.put(ch);
    }

}


ext_char decodeTree(Node *encodingTree, ibstream& infile) {
    
    
    if (encodingTree->character != NOT_A_CHAR) {
        return encodingTree->character;
    }
    int bit = infile.readBit();
    if (bit == 0) {
        return decodeTree(encodingTree->zero, infile);
    } else {
        return decodeTree(encodingTree->one, infile);
    }

  
}

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
    for(ext_char ch : frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}

}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
    Map<ext_char, int> frequencies = getFrequencyTable(infile);
    Node *encodingTree = buildEncodingTree(frequencies);
    writeFileHeader(outfile, frequencies);
    infile.rewind();
    encodeFile(infile, encodingTree, outfile);
    freeTree(encodingTree);
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
    Map<ext_char, int> frequencies = readFileHeader(infile);
    Node * encodingTree = buildEncodingTree(frequencies);
    decodeFile(infile, encodingTree, outfile);
    freeTree(encodingTree);
}

