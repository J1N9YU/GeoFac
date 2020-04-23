#include "MyDataAnalysisHelper.hh"

using namespace std;

MyDataAnalysisHelper* MyDataAnalysisHelper::fInstance = NULL;

MyDataAnalysisHelper::MyDataAnalysisHelper(){
    hitCount =0;
    totalCount = 0;
    fInstance=NULL;
    isSaving=false;
    numThread=1;
    reapeatEachThread = 1;
    experimentType = "undefined";
}

MyDataAnalysisHelper::~MyDataAnalysisHelper(){
    delete fInstance;
}

MyDataAnalysisHelper* MyDataAnalysisHelper::GetInstance(){
    if(!fInstance)fInstance=new MyDataAnalysisHelper();
    return fInstance;
}

void MyDataAnalysisHelper::AddHit(){hitCount++;}
double MyDataAnalysisHelper::GetHitRatio(){return (double)hitCount/(double)totalCount;}

void MyDataAnalysisHelper::Clear(){
    hitCount=0;
    totalCount=0;
}

void MyDataAnalysisHelper::WriteToFile(){
     if(!isSaving){
        G4cout<<"Saving is off"<<G4endl;
        return;
    }
    if(numThread!=1)ProcessRecord();



    //Writeing record to file
    G4cout<<"saving result to file..."<<G4endl;
    ofstream file("ResultData",ios::app);
    //get time
    time_t now = time(NULL);
    tm* now_tm= localtime(&now);
    string now_str = asctime(now_tm);
    //wtrite table head
    file<<endl<<now_str<<"type = "<<experimentType<<endl;
    file<<"index\ttotal\thit\tratio\ttime\t";
    if(numThread!=1)file<<"stdev\tnumTread = "<<numThread;
    file<<endl;
    //write data
    int i=0;
    for(auto r:record){
        file<<i++<<"\t"<<r.total<<"\t"<<r.hit<<"\t"<<r.ratio<<"\t"<<(double)r.comsumedTick/CLOCKS_PER_SEC;
        if(numThread!=1)file<<"\t"<<r.stdev;
        file<<endl;
    }
    //Write final result
    
    if(!GReemitV.empty()&&!GSourceV.empty()){
        record=GetRunRatio(GReemitV,GSourceV);
        ProcessRecord();
        file<<endl;
        file<<"Type = GeometryFactor"<<endl;
        file<<"total\tGeoFac\tStdev\ttime"<<endl;
        for(auto r:record){
            file<<r.total<<"\t"<<r.ratio<<"\t"<<r.stdev<<"\t"<<r.comsumedTick/CLOCKS_PER_SEC<<endl;
        }
    }
    record.clear();




    file.close();
    record.clear();
    G4cout<<"saving done!"<<G4endl;
}



void MyDataAnalysisHelper::WriteToRecord(){
    RnuRecord rec;
    rec.total = totalCount;
    rec.hit = hitCount;
    rec.ratio = GetHitRatio();
    rec.comsumedTick=deltaTick;
    record.push_back(rec);
}

void MyDataAnalysisHelper::ProcessRecord(){
    vector<RunRecord> newRec;
    int realNumThread = (numThread+1)*reapeatEachThread;
    int n = record.size()/realNumThread;
    if(record.size()%realNumThread!=0){G4cout<<"ProcessRecord Error, skip processing"<<G4endl;return;}

    for(auto r:record){
        if(experimentType=="source")GSourceV.push_back(r);
        if(experimentType=="reemit")GReemitV.push_back(r);
    }

    for(int i=0;i<n;i++){
        vector<double> rv;
        vector<int> hv;
        vector<clock_t> cv;
        for(int j=0;j<realNumThread;j++){
            int index= i*realNumThread+j;
            rv.push_back(record[index].ratio);
            hv.push_back(record[index].hit);
            cv.push_back(record[index].comsumedTick);
        }
        RunRecord r;
        r.total = record[i*realNumThread].total;
        r.hit= accumulate(hv.begin(),hv.end(),0.0)/hv.size();
        r.ratio=(double)accumulate(rv.begin(),rv.end(),0.0)/rv.size();
        r.comsumedTick = accumulate(cv.begin(),cv.end(),0)/cv.size();
        double mean = r.ratio;
        double stdev = 0.0;
        for(auto v:rv){
            stdev+=(v-mean)*(v-mean);
        }
        stdev/=rv.size();
        stdev=sqrt(stdev);
        r.stdev=stdev;
        newRec.push_back(r);
    }
    //record.insert(record.end(),newRec.begin(),newRec.end());
    swap(record,newRec);

    //seperate G value


    //This line is to keep the unprocessed data after process data is done.
    //record.insert(record.begin(),newRec.begin(),newRec.end());
    
}

vector<RunRecord> MyDataAnalysisHelper::GetRunRatio(vector<RunRecord> a,vector<RunRecord> b){
    vector<RunRecord> newRec;
    if(a.size()!=b.size()){
        G4cout<<"GetRunRatio error! Size of inputs are different"<<G4endl;
    }
    int n = a.size();
    for(int i=0;i<n;i++){
        RunRecord r;
        r.total = a[i].total;
        r.comsumedTick = a[i].comsumedTick+b[i].comsumedTick;
        r.ratio = (float)a[i].hit/b[i].hit;
        newRec.push_back(r);
    }
    return newRec;
}