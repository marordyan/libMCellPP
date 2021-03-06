/* File : libMCell.h */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdint>

using namespace std;

class MCellMoleculeInstance; // Forward declaration needed

class MCellMoleculeSpecies {
 public:
  string name;
  // char * new_name;
  string type;
  char type_code;
  double diffusion_constant;

  //vector<MCellMoleculeInstance *> instance_list;
  MCellMoleculeInstance *instance_list;
  int num_instances;

  MCellMoleculeSpecies() {
    name = "X";
    type = 'v';
    type_code = 0;
    diffusion_constant = 0.0;
    instance_list = NULL;
    num_instances = 0;
  }

};

class MCellMoleculeInstance {
 public:
  MCellMoleculeSpecies *molecule_species;
  double x, y, z;
  MCellMoleculeInstance *next;
};

class MCellReleaseSite {
 public:
  MCellMoleculeSpecies *molecule_species;
  double x, y, z;
  double quantity;
  MCellReleaseSite *next;
};

class MCellReaction {
 public:
  string reactants;
  string products;
  double forward_rate;
  double backward_rate;
  MCellReaction *next;
};

class MCellEvent {
 public:
  double time;
  MCellEvent() {
    time = 0.0;
  }
};

class MCellTimerEvent : public MCellEvent {
 public:
  MCellTimerEvent() {
    time = 0.0;
  }
  virtual void execute() {
    cout << "Default timer" << endl;
  }
};

class MCellMolCreationEvent : public MCellEvent {
 public:
  MCellMoleculeInstance *mol;
  MCellMolCreationEvent() {
    time = 0.0;
  }
  virtual void execute(MCellMoleculeInstance *mol) {
    cout << "Default molecule creation" << endl;
  }
};

class MCellSimulation {
 private:
  char *join_path ( char *p1, char sep, char *p2 );
  //void pick_displacement( MCellMoleculeInstance *mol, double scale /*, struct rng_state *rng */ );
 public:
  static int num_simulations; // Tracks number of simulations that have been created.

  uint32_t seed;

  int num_iterations;
  double time_step;

  vector<MCellTimerEvent *>timer_event_handlers;
  vector<MCellMolCreationEvent *>mol_creation_event_handlers;

  map<string, MCellMoleculeSpecies *>molecule_species;
  vector<MCellReleaseSite *>molecule_release_sites;
  vector<MCellReaction *>reactions;

  MCellSimulation() {
    num_simulations++;
    seed = 1;
    num_iterations = 0;
    time_step = 0.0;
  }
  virtual ~MCellSimulation() {
    num_simulations--;
  }

  void add_molecule_species ( MCellMoleculeSpecies *species );
  void add_molecule_release_site ( MCellReleaseSite *site );
  void add_reaction ( MCellReaction *rxn );
  MCellMoleculeSpecies *get_molecule_species_by_name ( char *mol_name );
  void run_simulation ( char *proj_path );
};

