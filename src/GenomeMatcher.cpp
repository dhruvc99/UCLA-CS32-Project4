//
//  GenomeMatcher.cpp
//  genomics
//
//  Created by Dhruv Chakraborty on 3/11/19.
//  Copyright © 2019 Dhruv Chakraborty. All rights reserved.
//

#include "provided.h"
#include "Trie.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

struct seqLabel
{
    string name;
    int pos;
    int index;
};

class GenomeMatcherImpl
{
public:
    GenomeMatcherImpl(int minSearchLength);
    void addGenome(const Genome& genome);
    int minimumSearchLength() const;
    bool findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const;
    bool findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const;
private:
    int m_minSearchLength;
    vector<Genome> m_genomeLibrary;
    Trie<seqLabel> m_sequenceTrie;
};

GenomeMatcherImpl::GenomeMatcherImpl(int minSearchLength)
                                    : m_minSearchLength(minSearchLength)
{}

void GenomeMatcherImpl::addGenome(const Genome& genome)
{
    m_genomeLibrary.push_back(genome);
    // loop below inserts all subsequences of length minSearchLength into Trie, using seqLabel struct to label each subsequence
    for (int i = 0; i <= genome.length() - minimumSearchLength(); i++)
    {
        string seqFragment;
        genome.extract(i, minimumSearchLength(), seqFragment);
        seqLabel label;
        label.name = genome.name();
        label.pos = m_genomeLibrary.size() - 1;
        label.index = i;
        m_sequenceTrie.insert(seqFragment, label);
    }
}

int GenomeMatcherImpl::minimumSearchLength() const
{
    return m_minSearchLength;
}

bool GenomeMatcherImpl::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    if (fragment.size() < minimumLength || minimumLength < minimumSearchLength())
        return false;
    
    vector<seqLabel> couldBeMatches = m_sequenceTrie.find(fragment.substr(0, minimumSearchLength()), exactMatchOnly);
    
    unordered_map<int, DNAMatch> DNAMatches;
    unordered_map<int, DNAMatch>::iterator it;
    
    for (int i = 0; i < couldBeMatches.size(); i++)
    {
        int pos = couldBeMatches[i].pos;
        int index = couldBeMatches[i].index;
        bool matchType = exactMatchOnly;
        
        string seq;
        m_genomeLibrary[pos].extract(index, minimumSearchLength(), seq);
        
        if (seq != fragment.substr(0, minimumSearchLength()))
            matchType = true;
        
        int j;  // use j for length
        for (j = minimumSearchLength(); j < fragment.size(); j++)
        {
            m_genomeLibrary[pos].extract(index, j + 1, seq);
            
            if (seq[j] != fragment[j])
            {
                if (matchType == true)
                    break;
                else
                    matchType = true;
            }
        }
        
        // add to DNAMatches if not already present. If already present and is longer, replace
        if (j >= minimumLength)
        {
            it = DNAMatches.find(pos);
            if (it != DNAMatches.end())
            {
                if (j > (it->second).length)
                {
                    (it->second).position = index;
                    (it->second).length = j;
                }
            }
            else
            {
                DNAMatches[pos] = {m_genomeLibrary[pos].name(), j, index};
            }
        }
    }
    
    it = DNAMatches.begin();
    while (it != DNAMatches.end())
    {
        matches.push_back(it->second);
        it++;
    }
        
    if (DNAMatches.empty())
        return false;
    return true;
}

bool sortGenomesBy(GenomeMatch genome1, GenomeMatch genome2)
{
    if (genome1.percentMatch == genome2.percentMatch)
        return genome1.genomeName < genome2.genomeName;
    else
        return genome1.percentMatch > genome2.percentMatch;
}

bool GenomeMatcherImpl::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    if (fragmentMatchLength < minimumSearchLength())
        return false;
    
    unordered_map<string, int> nameToCount;
    unordered_map<string, int>::iterator it;
    int fragNum = query.length()/fragmentMatchLength;
    
    for (int i = 0; i < m_genomeLibrary.size(); i++)
        nameToCount[m_genomeLibrary[i].name()] = 0;
    
    for (int i = 0; i < fragNum; i++)
    {
        string seq;
        query.extract(i*fragmentMatchLength, fragmentMatchLength, seq);
        vector<DNAMatch> matches;
        findGenomesWithThisDNA(seq, fragmentMatchLength, exactMatchOnly, matches);
        
        for (int j = 0; j < matches.size(); j++)
            nameToCount[matches[j].genomeName]++;
    }
    
    it = nameToCount.begin();
    while (it != nameToCount.end())
    {
        double percent = (double) ((it->second)*100/fragNum);
        if (percent > matchPercentThreshold)
        {
            GenomeMatch matchingGenome;
            matchingGenome.genomeName = it->first;
            matchingGenome.percentMatch = percent;
            results.push_back(matchingGenome);
        }
        it++;
    }
    
    sort(results.begin(), results.end(), sortGenomesBy);
    
    if (results.empty())
        return false;
    return true;
}

// ******************** GenomeMatcher functions ********************************

// These functions simply delegate to GenomeMatcherImpl's functions.
// You probably don't want to change any of this code.

GenomeMatcher::GenomeMatcher(int minSearchLength)
{
    m_impl = new GenomeMatcherImpl(minSearchLength);
}

GenomeMatcher::~GenomeMatcher()
{
    delete m_impl;
}

void GenomeMatcher::addGenome(const Genome& genome)
{
    m_impl->addGenome(genome);
}

int GenomeMatcher::minimumSearchLength() const
{
    return m_impl->minimumSearchLength();
}

bool GenomeMatcher::findGenomesWithThisDNA(const string& fragment, int minimumLength, bool exactMatchOnly, vector<DNAMatch>& matches) const
{
    return m_impl->findGenomesWithThisDNA(fragment, minimumLength, exactMatchOnly, matches);
}

bool GenomeMatcher::findRelatedGenomes(const Genome& query, int fragmentMatchLength, bool exactMatchOnly, double matchPercentThreshold, vector<GenomeMatch>& results) const
{
    return m_impl->findRelatedGenomes(query, fragmentMatchLength, exactMatchOnly, matchPercentThreshold, results);
}
