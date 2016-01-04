#include "trainningSet.h"

ostream&
operator<<(ostream& s,const Trainning_Set& t){
    for(unsigned i=0;i<t.set.size();++i){
        for(unsigned j=1;j<t.set[i].first.size();++j)
            s << t.set[i].first[j] << ",";
        s << t.set[i].second << endl;
    }
    return s;
}

//TODO ajustar parametro dimensiones automatico
Trainning_Set::Trainning_Set(const char* filename,int dimensions): set(){
    if(dimensions<1){
        cerr << "Error: cannot create Trainning Set of <1 dimensions" << endl;
        return;
    }else
        dim=dimensions;

    ifstream file;
    file.open(filename);
    if(file){
        string read;
        while(!file.eof()){
            getline(file,read);
            if(!read.empty())
                insert(read);
        }
        file.close();
    }else
        cerr << "Error al abrir el archivo "<< filename << endl;
}
/*
void
Trainning_Set::insert(const string& str){
    vector<double> x;
    x.push_back(1.0);
    string::size_type pos,last_pos;
    pos=0;
    last_pos=0;
    while(pos!=string::npos){
        pos=str.find(',',last_pos);
        if(pos!=string::npos){
        	x.push_back(stod(str.substr(last_pos,pos)));
        	last_pos=pos;
        	last_pos++;
        }else
            set.push_back(make_pair(x,stod(str.substr(last_pos))));
    }
}*/
void
Trainning_Set::insert(const string& str){
    vector<double> x;
    x.push_back(1.0);
    string::size_type pos,last_pos;
    last_pos=pos=0;
    while(pos!=string::npos){
        //last_pos=pos;
        pos=str.find(',',last_pos);
        if(pos!=string::npos) {
            x.push_back(stod(str.substr(last_pos,pos)));
            last_pos=pos;
            ++last_pos;
        }
        else
            set.push_back(make_pair(x,stod(str.substr(last_pos))));
    }
}

double
Trainning_Set::get_x(int ex,int pos) const{
    if(bound_check(ex,set.size()))
        if(bound_check(pos,set[ex].first.size()))
            return set[ex].first[pos];
    return 0.0;
}

double
Trainning_Set::get_y(int pos) const{
    if(bound_check(pos,set.size()))
        return set[pos].second;
    return 0.0;
}

const vector<double>&
Trainning_Set::get_x(int ex) const{
    return set[ex].first;
}

void
Trainning_Set::normalize(){
    norm.clear();
    for(unsigned i=1;i<=dim;++i)
        normalize_x(i);
    normalize_y();
}

/*
void
Trainning_Set::normalize_x(int x){
    double max,min,avg,range;
    max=min=avg=0.0;
    for(unsigned i=0;i<set.size();++i){
        if(max<set[i].first[x])
            max=set[i].first[x];
        if(min>set[i].first[x])
            min=set[i].first[x];
        avg+=set[i].first[x];
    }
    avg=avg/set.size();
    range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].first[x]=(set[i].first[x]-avg)/range;
    }
}
void
Trainning_Set::normalize_y(){
    double max,min,avg,range;
    max=min=avg=0.0;
    for(unsigned i=0;i<set.size();++i){
        if(max<set[i].second)
            max=set[i].second;
        if(min>set[i].second)
            min=set[i].second;
        avg+=set[i].second;
    }
    avg=avg/set.size();
    range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].second=(set[i].second-avg)/range;
    }
}
*/
void
Trainning_Set::normalize_x(int x){
    double max,min,avg,range,elem;
    avg=0.0;

    //max=min=avg=0.0;
    //(set.size()>0)
    //? max=min=0.0
    //: max=min=set[0].first[x];
    if (set.size()>0)
        max=min=set[0].second;
    else
        return;

    for(unsigned i=0;i<set.size();++i){
        elem = set[i].first[x];
        if(max<elem)
            max=elem;
        else if(min>elem)
            min=elem;
        avg+=elem;
    }
    avg=avg/set.size();
    range=max-min;
    norm.push_back(make_pair(avg,range));
    //norm[x].first  = avg=avg/set.size();
    //norm[x].second = range=max-min;

    for(unsigned i=0;i<set.size();++i){ //Normalization.
        set[i].first[x]=(set[i].first[x]-avg)/range;
    }
}


void
Trainning_Set::normalize_y(){
    double max,min,avg,range,elem;
    avg=0.0;
    //max=min=avg=0.0;
    //(set.size()>0)
    //? max=min=0.0
    //: max=min=set[0].second;
    if (set.size()>0)
        max=min=set[0].second;
    else
        return;

    for(unsigned i=0;i<set.size();++i){
        elem = set[i].second;
        if(max<elem)
            max=elem;
        if(min>elem)
            min=elem;
        avg+=elem;
    }
    avg=avg/set.size();
    range=max-min;
    norm.push_back(make_pair(avg,range));
    //norm[dim +1].first  = avg=avg/set.size();
    //norm[dim +1].second = range=max-min;

    for(unsigned i=0;i<set.size();++i){
        set[i].second=(set[i].second-avg)/range;
    }
}
