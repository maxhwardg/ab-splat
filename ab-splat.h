#ifndef ABSPLAT_H
#define ABSPLAT_H

#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include "rnainterval.h"
#include "vienna.h"

std::string get_dotbracket(int rna_sz, const std::vector<RNAInterval>& windows, 
	const std::vector<int>& selected)
{
	std::string windowsStruct(rna_sz, '.');
	for(int k = 0; k < selected.size(); ++k)
	{
		int push = windows[selected[k]].left;

		for(int l = 0; l < windows[selected[k]].sstruct.size(); ++l)
			windowsStruct[push+l] = windows[selected[k]].sstruct[l];

	}
	return windowsStruct;
}

int threshold(int rna_size) 
{
	return sqrt(rna_size) * 9.5;
}


std::vector<int> weighted_activity_selection(std::vector<RNAInterval>& intervals)
{
	//sort by right end point
	std::sort( intervals.begin(), intervals.end() );
	std::vector<int> q(intervals.size()+1, 0);
	//compute q values
	for(int i = 1; i < intervals.size(); ++i)
	{
		//binary search for last compatible index
		int l = 0, r = i-1, mid;
		while(l <= r)
		{
			mid = l + (r-l)/2;
			if(intervals[mid].right < intervals[i].left 
				&& !(intervals[mid+1].right < intervals[i].left))
			{
				q[i+1] = mid+1;
				break;
			}
			else if(intervals[i].left > intervals[mid].right)
				l = mid+1;
			else
				r = mid-1;
		}

	}
	std::vector<double> dp(intervals.size()+1);
	//bottom up dp fill
	dp[0] = 0;
	for(int i = 1; i < dp.size(); ++i)
	{
		double iScore = intervals[i-1].score + dp[q[i]];
		if(iScore > dp[i-1])
			dp[i] = iScore;
		else
			dp[i] = dp[i-1];
	}
	//traceback
	int curr = intervals.size();
	std::vector<int> traced;
	while(curr > 0)
	{
		if (intervals[curr-1].score + dp[q[curr]] > dp[curr-1])
		{
			traced.push_back(curr-1);
			curr = q[curr];
		}
		else
			--curr;
	}
	std::reverse(traced.begin(), traced.end());
	return traced;
}

std::string ab_splat(int a, float b, const std::string& rna) 
{

	std::vector<RNAInterval> all_windows;

	int t = threshold(rna.size());

	for (int i = a; i < t; i = (float) i * b)
	{
		std::vector<RNAInterval> windows = rnal_fold(rna, i);
		all_windows.insert(all_windows.end(), 
			windows.begin(), windows.end());
	}
	

	std::vector<int> selected_windows = 
		weighted_activity_selection(all_windows);

	return get_dotbracket(rna.size(), all_windows, selected_windows);

}

#endif
