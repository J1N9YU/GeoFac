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
    GReemitLatest = 0;
    GSourceLatest = 0;
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

    //Getting the reuslt with most amount of runs.
    G4double GLatest = record[record.size()-1].ratio;
    if(experimentType=="source")GSourceLatest = GLatest;
    else if(experimentType=="reemit")GReemitLatest = GLatest;

    //Writeing record to file
    G4cout<<"saving result to file..."<<G4endl;
    ofstream file("ResultData",ios::app);
    //get time
    time_t now = time(NULL);
    tm* now_tm= localtime(&now);
    string now_str = asctime(now_tm);
    //wtrite table head
    file<<endl<<now_str<<"type = "<<experimentType;
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
    file.close();
    record.clear();
    G4cout<<"saving done!"<<G4endl;
    
    if(GSourceLatest!=0&&GReemitLatest!=0)G4cout<<"The result of geometry factor is:\t"<<GReemitLatest/GSourceLatest<<G4endl;
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
    vector<double> rv;
    vector<int> hv;
    vector<clock_t> cv;
    for(int i=0;i<n;i++){
        for(int j=0;j<realNumThread;j++){
            int index= i*realNumThread+j;
            rv.push_back(record[index].ratio);
            hv.push_back(record[index].hit);
            cv.push_back(record[index].comsumedTick);
        }
        RunRecord r;
        r.total = record[i*realNumThread].total;
        r.hit= accumulate(hv.begin(),hv.end(),0)/hv.size();
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
}