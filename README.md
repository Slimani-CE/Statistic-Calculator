#Statistic Calculator

#Inputs
let's firstly talk about the simple side, "the inputs"
the programme takes as inputs the number of table cases (N)
after that takes N couples of inputs xi and ni, That's all

#Little mathematics explanations
if you are studying statistics in your school or university, so this little programme will help you to calculate and complete the statistic table.
firstly if you did't understand what i'm talking about; i will explain:
From the sample data, we can calculate a statistic. A statistic is a number that represents a property of the sample. For example, if we consider one math class to be a sample of the population of all math classes, then the average number of points earned by students in that one math class at the end of the term is an example of a statistic. The statistic is an estimate of a population parameter. A parameter is a number that is a property of the population. Since we considered all math classes to be the population, then the average number of points earned per student over all the math classes is an example of a parameter.

we take a population of a data, and we organize each value (xi) and the number of her occurrence (ni) and organize them In ascending order in a table 
like this:
________________________________________________________________________________________________________________________
|  xi  #     2.5000  #     6.0000  #     8.5000  #    11.0000  #    13.5000  #    16.0000  #    18.5000  #    22.5000  |
########################################################################################################################
########################################################################################################################
|  ni  #     30      #     45      #    110      #    250      #    150      #     60      #     35      #     20      |
########################################################################################################################

### N=the sum of ni ( for this table N=700. )
### Ni of each set is the sum from n0 to ni and for the example above we have:
########################################################################################################################
|   Ni  #    30.0000 #    75.0000  #   185.0000  #   435.0000  #   585.0000  #   645.0000  #   680.0000  #   700.0000  |
########################################################################################################################


###some statistical parameters that the programme can calculate

1. Measures of Frequency:
* Count(ni)

* Percent(pi)=(ni/N)*100

* Frequency(fi)=ni/N

* Shows how often something occurs

2. Measures of Central Tendency
* Mean(Xbar)=the sum of ni*xi devied by N

* Median(Xmed)= is the smallest xi wich her Ni is higher then N/2 ; for the example above Xmed=x4=11 because N4=435 is the
  smallest value wich is bigger then N/2=350.

* Mode(Xmode)=is an xi wich her ni appears most often; for the example above Xmod=x4=11 because n4 is biggest value.


* Use this when you want to show how an average or most commonly indicated response

3. Measures of Dispersion or Variation

* Range or e(X)=if nmax is the biggest ni and nmin in the smallest one so; e(X)=nmax-nmin

* Variance(var)=(the sum of ni*(xi-Xbar)^2)/N

* Standard Deviation (the square root of the variance (Sdev)) Sdev=sqrt(var)

* Identifies the spread of scores by stating intervals

* Use this when you want to show how "spread out" the data are. It is helpful to know when your data are so spread out that it affects the mean
