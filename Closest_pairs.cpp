#include <bits/stdc++.h>
using namespace std;

inline double getDistance(pair<int,int>& p1, pair<int,int>& p2){
    double xdif = p1.first-p2.first;
    double ydif = p1.second-p2.second;
    return sqrt(xdif*xdif+ydif*ydif);
}

double minimal_distance_naive(vector<pair<int,int> >& points,int left, int right){
    double min_distance = DBL_MAX;
    for(int i=left;i<right-1;i++){
        for(int j=i+1;j<right;j++){
            double dist = getDistance(points[i],points[j]);
            if(dist<min_distance)
                min_distance = dist;
        }
    }
    return min_distance;
}

void strip_closest(vector<pair<int,int> >& points, double& min_dist){
    sort(points.begin(),points.end());
    int n = points.size();
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            double dist = getDistance(points[i],points[j]);
            if(dist>min_dist)
                break;
            min_dist = dist;
        }
    }
}

double minimal_distance(vector<pair<int,int> >& points, int left, int right) {
    if(right-left<=3)
        return minimal_distance_naive(points,left,right);
    int mid = (left+right)/2;
    double dist = min(minimal_distance(points,left,mid),minimal_distance(points,mid,right));
    vector<pair<int,int> > strip;
    int midx = points[mid].first;
    for(int i=left;i<right;i++){
        if(abs(points[i].first-midx)<dist)
            strip.push_back(make_pair(points[i].second,points[i].first));
    }
    strip_closest(strip,dist);
    return dist;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie();
  cout.tie(NULL);
  size_t n;
  cin >> n;
  vector<pair<int,int> > points(n);
  int x,y;
  for (size_t i = 0; i < n; i++) {
    cin >> points[i].first >> points[i].second;
  }
  sort(points.begin(),points.end());
  cout << std::fixed;
  cout << setprecision(9) << minimal_distance(points,0,n) << "\n";
}
