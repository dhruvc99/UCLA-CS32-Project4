//
//  Genome.cpp
//  genomics
//
//  Created by Dhruv Chakraborty on 3/11/19.
//  Copyright © 2019 Dhruv Chakraborty. All rights reserved.
//

#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <istream>
using namespace std;

class GenomeImpl
{
public:
    GenomeImpl(const string& nm, const string& sequence);
    static bool load(istream& genomeSource, vector<Genome>& genomes);
    int length() const;
    string name() const;
    bool extract(int position, int length, string& fragment) const;
private:
    string m_name;
    string m_DNAsequence;
};

GenomeImpl::GenomeImpl(const string& nm, const string& sequence)
                      : m_name(nm), m_DNAsequence(sequence)
{}

bool GenomeImpl::load(istream& genomeSource, vector<Genome>& genomes)
{
    string name = "";
    string DNAsequence = "";
    string storeLine = "";
    bool firstGenome = true;
    
    while (getline(genomeSource, storeLine))
    {
        if (storeLine[0] == '>')
        {
            if (firstGenome)
                firstGenome = false; // ensures that we don't add first genome until getting it's sequence
            else
            {
                genomes.push_back(Genome(name, DNAsequence));
                DNAsequence = "";
            }
            name = storeLine.substr(1);
            if (name == "")
                return false;
        }
        else
        {
            for (int i = 0; i < storeLine.size(); i++)
            {
                char base = toupper(storeLine[i]);
                switch (base)
                {
                    case 'A':
                    case 'C':
                    case 'T':
                    case 'G':
                    case 'N':
                        DNAsequence += base;
                        break;
                    default:
                        return false;
                }
            }
        }
    }
    
    genomes.push_back(Genome(name, DNAsequence)); // takes care of last genome since no '>' succeeding it
    return true;
}

int GenomeImpl::length() const
{
    return m_DNAsequence.size();
}

string GenomeImpl::name() const
{
    return m_name;
}

bool GenomeImpl::extract(int position, int length, string& fragment) const
{
    if (position < 0 || length < 0 || m_DNAsequence.size() < (position + length))
        return false;
    fragment = m_DNAsequence.substr(position, length);
    return true;
}

//******************** Genome functions ************************************

// These functions simply delegate to GenomeImpl's functions.
// You probably don't want to change any of this code.

Genome::Genome(const string& nm, const string& sequence)
{
    m_impl = new GenomeImpl(nm, sequence);
}

Genome::~Genome()
{
    delete m_impl;
}

Genome::Genome(const Genome& other)
{
    m_impl = new GenomeImpl(*other.m_impl);
}

Genome& Genome::operator=(const Genome& rhs)
{
    GenomeImpl* newImpl = new GenomeImpl(*rhs.m_impl);
    delete m_impl;
    m_impl = newImpl;
    return *this;
}

bool Genome::load(istream& genomeSource, vector<Genome>& genomes)
{
    return GenomeImpl::load(genomeSource, genomes);
}

int Genome::length() const
{
    return m_impl->length();
}

string Genome::name() const
{
    return m_impl->name();
}

bool Genome::extract(int position, int length, string& fragment) const
{
    return m_impl->extract(position, length, fragment);
}
