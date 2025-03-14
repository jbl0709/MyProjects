#include <iostream>
#include <string>
#include <utility>
#include <algorithm> //reverse
#include <fstream>
using namespace std;

char complement(char const x)
{
    // geht switch maybe?
    if(x == 'A'){return 'T';}
    else if (x =='T'){return'A';}
    else if (x == 'G'){return 'C';}
    else if (x == 'C'){return 'G';}
    else {return '!';} //keine DNA Base eingegeben
}

string reverseComplement(string const& input)
{
    string output;
    if (input.length() == 0){return "";} // Wenn input leer ist 
    // komplementären String erstellen
    for (size_t i = 0; i < input.length(); i++)
    {
        output += complement(input.at(i));
    }
    // reverse den string 
    reverse(output.begin(), output.end());
    return output;
}

pair<string, string> readFasta(string const & in_file)
{
    ifstream myfile(in_file); //lesen der datei in_file
    string meta; 
    string seq; 
    string temp; 
    string line;

    if (myfile.is_open()){
        getline(myfile, meta); // erste Zeile als meta definieren
        // restliche Zeilen zum string sequenz hinzufügen
        while(getline(myfile, line)){
            seq += line;
        }
        // alle leerzeichen entfernen und returns
        for(size_t i = 0; i < seq.length(); i++){
            if (seq.at(i) == '\n' || seq.at(i) == ' '){continue;}
            else temp += seq.at(i);
        }
    seq = temp; 
    }
    return {meta, seq};
}


bool writeFasta(std::string const& out_file, 
                std::string const& meta, 
                std::string const& seq)
{
    std::ofstream myfile(out_file); //file öffnen zum reinschreiben
    if (myfile.is_open())
    {
        myfile << meta << "\n"; // meta zeile 
        // Alle 80 zeichen ein zeichenumbruch, um FASTA Format zu erhalten
        for(size_t i = 0; i < seq.length(); i++)
        {
            // Überprüfen, ob sequence korrekt ist, wenn nicht false
            if(seq.at(i) != 'A' && seq.at(i) != 'G' && seq.at(i) != 'C' && seq.at(i) != 'T'){return false;}
            if (i % 80 == 0 && i > 79) {myfile << '\n';} // alle 80 Zeichen '\n' einfügen
            myfile << seq.at(i);
        }
        return true; // wenn alles klappt, dann true, sonst false
    }
    else return false;
}


bool reverseComplementFASTA(std::string const& input_file,
                            std::string const& output_file)
{
    pair<string, string> const temp_pair = readFasta(input_file); // fasta datei lesen
    string header = get<0>(temp_pair); // meta
    string sequence = get<1>(temp_pair); // sequence
    sequence = reverseComplement(sequence); //sequenz umdrehen und komplement erstellen
    //überprüfen ob alles geklappt hat und Fasta Datei schreiben
    return writeFasta(output_file, header, sequence);
}
