%{
#include "algorithm.h"
%}
namespace essentia
{
    template <class T>
    class OrderedMap : public std::vector<std::pair<std::string, T*> > {
    public:
    
    typedef typename std::vector<std::pair<std::string, T*> > BaseClass;

    int size() const;
    
    %extend {
        T* __getitem__(const char * str) { return (*$self)[str]; }        
        T* getpair(uint idx, std::string& s) { 
            auto r = (*$self)[idx]);
            s   = r.first;
            return r.second;
        }
        void setpair(uint idx, const std::string & s, T * v) {
            auto r = (*$self)[idx]);
            r.first = s;
            r.second = v;
        }
    }
    
    std::vector<std::string> keys() const;
    void insert(const std::string& key, T* value);
    };
}

namespace essentia::standard
{
class Algorithm : public Configurable 
{
 public:
  static const std::string processingMode;
  typedef OrderedMap<InputBase> InputMap;
  typedef OrderedMap<OutputBase> OutputMap;
  DescriptionMap inputDescription;
  DescriptionMap outputDescription;

 public:

  virtual ~Algorithm();

  const InputMap& inputs() const;
  const OutputMap& outputs() const;

  /**
   * Return the input wrapper associated with the given name.
   */
  InputBase& input(const std::string& name);

  /**
   * Return the output wrapper associated with the given name.
   */
  OutputBase& output(const std::string& name);

  /**
   * Return the names of all the inputs that have been defined for this object.
   */
  std::vector<std::string> inputNames() const;

  /**
   * Return the names of all the outputs that have been defined for this object.
   */
  std::vector<std::string> outputNames() const;

  /**
   * Do the actual computation once that everything is set and configured.
   * The recommended use for this function is to first get the inputs and
   * outputs into local ref variables (const for the inputs) and then do the
   * processing.
   * This allow you also to write a "classic" function call with parameters
   * which you would just wrap with the parameterless function.
   */
  virtual void compute() = 0;

  /**
   * This function will be called when doing batch computations between each
   * file that is processed. That is, if your algorithm is some sort of state
   * machine, it allows you to reset it to its original state to process
   * another file without having to delete and reinstantiate it.
   */
  virtual void reset() {}


  // methods for having access to the types of the inputs/outputs
  std::vector<const std::type_info*> inputTypes() const;
  std::vector<const std::type_info*> outputTypes() const;

};


} // namespace essentia

namespace essentia {

    template <typename BaseAlgorithm>
    class AlgorithmInfo {
    public:
    
        typedef BaseAlgorithm* (*AlgorithmCreator)();
        AlgorithmCreator create;
        std::string name; // do we need this one or is it redundant
        std::string description;
        std::string category;
    };


    template <typename BaseAlgorithm>
    class EssentiaFactory {
    public:

        static void init();
        static void shutdown();
        static BaseAlgorithm* create(const std::string& id);
        static void free(BaseAlgorithm* algo);
        static std::vector<std::string> keys();
        static const AlgorithmInfo<BaseAlgorithm>& getInfo(const std::string& id);   
        static EssentiaFactory& instance();

        protected:
        // protected constructor to ensure singleton.
        EssentiaFactory() {}
        EssentiaFactory(EssentiaFactory&);

        //typedef EssentiaMap<std::string, AlgorithmInfo<BaseAlgorithm>, string_cmp> CreatorMap;
        //CreatorMap _map;
        // it goes to 25 of these...
        //static BaseAlgorithm* create(const std::string & id1, const Parameter& value value1);
        //BaseAlgorithm* create_i(const std::string& id1);

        template <typename ConcreteProduct, typename ReferenceConcreteProduct = ConcreteProduct> class Registrar;
    };

    template <typename ConcreteProduct, typename ReferenceConcreteProduct = ConcreteProduct>
    class EssentiaFactory::Registrar {
    public:
        Registrar();
        static BaseAlgorithm* create();
    };
} // namespace essentia
