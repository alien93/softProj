#include "experiment.h"

Experiment::Experiment(MyGLWidget robotSimulator)
{
    this->robotSimulator = robotSimulator;
}

vector<double> Experiment::generateTestData()
{
    vector<double> retVal;

    random_device rd; // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_real_distribution<> hipDistribution(-0.52, 1.57);   // define the range (from -30 to 90 degrees)
    uniform_real_distribution<> kneeDistribution(-1.57, 0);     //(from -90 to 0 degrees)
    uniform_real_distribution<> ankleDistribution(-1.57, 0.52);  //(from -90 to 30 degrees)

    qDebug()<<"Generating test data...";
    for(int n=0; n<40; ++n)
    {
        retVal.push_back(1.0);
        retVal.push_back(hipDistribution(eng));
        retVal.push_back(hipDistribution(eng));
        retVal.push_back(kneeDistribution(eng));
        retVal.push_back(kneeDistribution(eng));
        retVal.push_back(ankleDistribution(eng));
        retVal.push_back(ankleDistribution(eng));
    }
    qDebug()<<"Generated";

    return retVal;
}

Population *Experiment::roboWalk_test(int gens)
{
    NEAT::load_neat_params("/home/nina/Documents/demo/softProj/RoboWalk/ann/robowalkparams.ne", true);

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

    ifstream iFile("/home/nina/Documents/demo/softProj/RoboWalk/ann/robowalkstartgenes",ios::in);

    cout<<"START ROBOWALK TEST"<<endl;

    cout<<"Reading in the start genome"<<endl;
    //Read in the start Genome
    iFile>>curword;
    iFile>>id;
    cout<<"Reading in Genome id "<<id<<endl;
    start_genome=new Genome(id,iFile);
    iFile.close();

    for(expcount=0;expcount<NEAT::num_runs;expcount++)
    {
        //Spawn the Population
        cout<<"Spawning Population off Genome2"<<endl;

        pop=new Population(start_genome,NEAT::pop_size);

        cout<<"Verifying Spawned Pop"<<endl;
        pop->verify();

        for (gen=1;gen<=gens;gen++)
        {
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
            if (roboWalk_epoch(pop,gen,temp,winnernum,winnergenes,winnernodes)) {
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

int Experiment::roboWalk_epoch(Population *pop, int generation, char *filename, int &winnernum, int &winnergenes, int &winnernodes)
{
    vector<Organism*>::iterator curorg;
    vector<Species*>::iterator curspecies;

    bool win=false;


    //Evaluate each organism on a test
    for(curorg=(pop->organisms).begin();curorg!=(pop->organisms).end();++curorg) {
        if (roboWalk_evaluate(*curorg)) {
            win=true;
            winnernum=(*curorg)->gnome->genome_id;
            winnergenes=(*curorg)->gnome->extrons();
            winnernodes=((*curorg)->gnome->nodes).size();
            if (winnernodes==5) {
                //You could dump out optimal genomes here if desired
                //(*curorg)->gnome->print_to_filename("xor_optimal");
                //cout<<"DUMPED OPTIMAL"<<endl;
            }
        }
    }

    //Average and max their fitnesses for dumping to file and snapshot
    for(curspecies=(pop->species).begin();curspecies!=(pop->species).end();++curspecies) {

        //This experiment control routine issues commands to collect ave
        //and max fitness, as opposed to having the snapshot do it,
        //because this allows flexibility in terms of what time
        //to observe fitnesses at

        (*curspecies)->compute_average_fitness();
        (*curspecies)->compute_max_fitness();
    }

    //Take a snapshot of the population, so that it can be
    //visualized later on
    //if ((generation%1)==0)
    //  pop->snapshot();

    //Only print to file every print_every generations
    if  (win||
         ((generation%(NEAT::print_every))==0))
        pop->print_to_file_by_species(filename);


    if (win) {
        for(curorg=(pop->organisms).begin();curorg!=(pop->organisms).end();++curorg) {
            if ((*curorg)->winner) {
                cout<<"WINNER IS #"<<((*curorg)->gnome)->genome_id<<endl;
                //Prints the winner to file
                //IMPORTANT: This causes generational file output!
                print_Genome_tofile((*curorg)->gnome,"robowalk_winner");
            }
        }

    }

    pop->epoch(generation);

    if (win) return ((generation-1)*NEAT::pop_size+winnernum);
    else return 0;

}

bool Experiment::roboWalk_evaluate(Organism *org)
{
    Network *net;
    int numnodes; //how many nodes should be visited during activation
    int thresh; //how many vists will be allowed before giving up (loop detection)


    net = org->net;
    numnodes = ((org->gnome)->nodes).size();
    thresh = numnodes*2;    //max number of visits allowed per activation

    org->fitness = robotSimulator->animateAnn(net, thresh);

#ifndef NO_SCREEN_OUT
    cout<<"Org "<<(org->gnome)->genome_id<<" fitness: "<<org->fitness<<endl;
#endif

    //Decide if its a winner
    if (org->fitness>=MAX_STEPS)
    {
        org->winner=true;
        return true;
    }
    else {
        org->winner=false;
        return false;
    }
}
