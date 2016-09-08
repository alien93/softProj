#include "experiment.h"

Experiment::Experiment()
{

}

void Experiment::generateTestData()
{
    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_real_distribution<> hipDistribution(-0.52, 1.57);   // define the range (from -30 to 90 degrees)
    uniform_real_distribution<> kneeDistribution(-1.57, 0);     //(from -90 to 0 degrees)
    uniform_real_distribution<> ankleDistribution(-1.57, 0.52);  //(from -90 to 30 degrees)

    qDebug()<<"Generating test data...";
    for(int n=0; n<40; ++n)
    {
        qDebug()<<"-------------------------------";
        qDebug()<<hipDistribution(eng);
        qDebug()<<hipDistribution(eng);
        qDebug()<<kneeDistribution(eng);
        qDebug()<<kneeDistribution(eng);
        qDebug()<<ankleDistribution(eng);
        qDebug()<<ankleDistribution(eng);
        qDebug()<<"-------------------------------";
    }
    qDebug()<<"Generated";
}

Population *Experiment::roboWalk_test(int gens)
{
    Population *pop = 0;
    Genome *start_genome;
    char curword[20];
    int id;

    ostringstream *fnamebuf;
    int gen;

    int evals[NEAT::num_runs];  //Hold records for each run
    int genes[NEAT::num_runs];
    int nodes[NEAT::num_runs];

    int winnernum;
    int winnergenes;
    int winnernodes;
    //For averaging
    int totalevals=0;
    int totalgenes=0;
    int totalnodes=0;
    int expcount;
    int samples;  //For averaging

    memset (evals, 0, NEAT::num_runs * sizeof(int));
    memset (genes, 0, NEAT::num_runs * sizeof(int));
    memset (nodes, 0, NEAT::num_runs * sizeof(int));

    ifstream iFile("robowalkstartgenes",ios::in);

    cout<<"START ROBOWALK TEST"<<endl;

    cout<<"Reading in the start genome"<<endl;
    //Read in the start Genome
    iFile>>curword;
    iFile>>id;
    cout<<"Reading in Genome id "<<id<<endl;
    start_genome=new Genome(id,iFile);
    iFile.close();

    /*for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      //Spawn the Population
      cout<<"Spawning Population off Genome2"<<endl;

      pop=new Population(start_genome,NEAT::pop_size);

      cout<<"Verifying Spawned Pop"<<endl;
      pop->verify();

      for (gen=1;gen<=gens;gen++) {
    cout<<"Epoch "<<gen<<endl;

    //This is how to make a custom filename
    fnamebuf=new ostringstream();
    (*fnamebuf)<<"gen_"<<gen<<ends;  //needs end marker

    #ifndef NO_SCREEN_OUT
    cout<<"name of fname: "<<fnamebuf->str()<<endl;
    #endif

    char temp[50];
    sprintf (temp, "gen_%d", gen);

    //Check for success
    if (xor_epoch(pop,gen,temp,winnernum,winnergenes,winnernodes)) {
      //	if (xor_epoch(pop,gen,fnamebuf->str(),winnernum,winnergenes,winnernodes)) {
      //Collect Stats on end of experiment
      evals[expcount]=NEAT::pop_size*(gen-1)+winnernum;
      genes[expcount]=winnergenes;
      nodes[expcount]=winnernodes;
      gen=gens;

    }

    //Clear output filename
    fnamebuf->clear();
    delete fnamebuf;

      }

      if (expcount<NEAT::num_runs-1) delete pop;

    }

    //Average and print stats
    cout<<"Nodes: "<<endl;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<nodes[expcount]<<endl;
      totalnodes+=nodes[expcount];
    }

    cout<<"Genes: "<<endl;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<genes[expcount]<<endl;
      totalgenes+=genes[expcount];
    }

    cout<<"Evals "<<endl;
    samples=0;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<evals[expcount]<<endl;
      if (evals[expcount]>0)
      {
    totalevals+=evals[expcount];
    samples++;
      }
    }

    cout<<"Failures: "<<(NEAT::num_runs-samples)<<" out of "<<NEAT::num_runs<<" runs"<<endl;
    cout<<"Average Nodes: "<<(samples>0 ? (double)totalnodes/samples : 0)<<endl;
    cout<<"Average Genes: "<<(samples>0 ? (double)totalgenes/samples : 0)<<endl;
    cout<<"Average Evals: "<<(samples>0 ? (double)totalevals/samples : 0)<<endl;
*/
    return pop;
}


/*
Population *xor_test(int gens) {
    Population *pop=0;
    Genome *start_genome;
    char curword[20];
    int id;

    ostringstream *fnamebuf;
    int gen;

    int evals[NEAT::num_runs];  //Hold records for each run
    int genes[NEAT::num_runs];
    int nodes[NEAT::num_runs];
    int winnernum;
    int winnergenes;
    int winnernodes;
    //For averaging
    int totalevals=0;
    int totalgenes=0;
    int totalnodes=0;
    int expcount;
    int samples;  //For averaging

    memset (evals, 0, NEAT::num_runs * sizeof(int));
    memset (genes, 0, NEAT::num_runs * sizeof(int));
    memset (nodes, 0, NEAT::num_runs * sizeof(int));

    ifstream iFile("xorstartgenes",ios::in);

    cout<<"START XOR TEST"<<endl;

    cout<<"Reading in the start genome"<<endl;
    //Read in the start Genome
    iFile>>curword;
    iFile>>id;
    cout<<"Reading in Genome id "<<id<<endl;
    start_genome=new Genome(id,iFile);
    iFile.close();

    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      //Spawn the Population
      cout<<"Spawning Population off Genome2"<<endl;

      pop=new Population(start_genome,NEAT::pop_size);

      cout<<"Verifying Spawned Pop"<<endl;
      pop->verify();

      for (gen=1;gen<=gens;gen++) {
    cout<<"Epoch "<<gen<<endl;

    //This is how to make a custom filename
    fnamebuf=new ostringstream();
    (*fnamebuf)<<"gen_"<<gen<<ends;  //needs end marker

    #ifndef NO_SCREEN_OUT
    cout<<"name of fname: "<<fnamebuf->str()<<endl;
    #endif

    char temp[50];
    sprintf (temp, "gen_%d", gen);

    //Check for success
    if (xor_epoch(pop,gen,temp,winnernum,winnergenes,winnernodes)) {
      //	if (xor_epoch(pop,gen,fnamebuf->str(),winnernum,winnergenes,winnernodes)) {
      //Collect Stats on end of experiment
      evals[expcount]=NEAT::pop_size*(gen-1)+winnernum;
      genes[expcount]=winnergenes;
      nodes[expcount]=winnernodes;
      gen=gens;

    }

    //Clear output filename
    fnamebuf->clear();
    delete fnamebuf;

      }

      if (expcount<NEAT::num_runs-1) delete pop;

    }

    //Average and print stats
    cout<<"Nodes: "<<endl;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<nodes[expcount]<<endl;
      totalnodes+=nodes[expcount];
    }

    cout<<"Genes: "<<endl;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<genes[expcount]<<endl;
      totalgenes+=genes[expcount];
    }

    cout<<"Evals "<<endl;
    samples=0;
    for(expcount=0;expcount<NEAT::num_runs;expcount++) {
      cout<<evals[expcount]<<endl;
      if (evals[expcount]>0)
      {
    totalevals+=evals[expcount];
    samples++;
      }
    }

    cout<<"Failures: "<<(NEAT::num_runs-samples)<<" out of "<<NEAT::num_runs<<" runs"<<endl;
    cout<<"Average Nodes: "<<(samples>0 ? (double)totalnodes/samples : 0)<<endl;
    cout<<"Average Genes: "<<(samples>0 ? (double)totalgenes/samples : 0)<<endl;
    cout<<"Average Evals: "<<(samples>0 ? (double)totalevals/samples : 0)<<endl;

    return pop;

}


*/
