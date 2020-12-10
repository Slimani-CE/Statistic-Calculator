#Calculatrice statistique

#Contributions
parlons d'abord du côté simple, "les entrées"
le programme prend comme entrées le nombre de cas de table (N)
après cela prend N couples d'entrées xi et ni, c'est tout

#Petites explications mathématiques
si vous étudiez les statistiques dans votre école ou université, ce petit programme vous aidera à calculer et à compléter le tableau statistique.
d'abord si vous n'avez pas compris de quoi je parle; Je vais expliquer:
À partir des exemples de données, nous pouvons calculer une statistique. Une statistique est un nombre qui représente une propriété de l'échantillon. Par exemple, si nous considérons une classe de mathématiques comme un échantillon de la population de toutes les classes de mathématiques, le nombre moyen de points gagnés par les élèves de cette classe de mathématiques à la fin du trimestre est un exemple de statistique. La statistique est une estimation d'un paramètre de population. Un paramètre est un nombre qui est une propriété de la population. Puisque nous avons considéré toutes les classes de mathématiques comme la population, le nombre moyen de points gagnés par élève sur toutes les classes de mathématiques est un exemple de paramètre.

nous prenons une population d'une donnée, et nous organisons chaque valeur (xi) et le numéro de son occurrence (ni) et les organisons par ordre croissant dans un tableau comme celui-ci:
########################################################################################################################
#  xi  #     2.5000  #     6.0000  #     8.5000  #    11.0000  #    13.5000  #    16.0000  #    18.5000  #    22.5000  #
########################################################################################################################
########################################################################################################################
#  ni  #     30      #     45      #    110      #    250      #    150      #     60      #     35      #     20      #
########################################################################################################################

# N = la somme de ni
   pour ce tableau N = 700.
# Ni de chaque ensemble est la somme de n0 à ni et pour l'exemple ci-dessus, nous avons:
########################################################################################################################
#   Ni  #    30.0000 #    75.0000  #   185.0000  #   435.0000  #   585.0000  #   645.0000  #   680.0000  #   700.0000  #
########################################################################################################################


#certains paramètres statistiques que le programme peut calculer

1. Mesures de fréquence:
* Count(ni)

* pourcentage(pi)=(ni/N)*100

* fréquence(fi)=ni/N

* Montre à quelle fréquence quelque chose se produit

2. Mesures des paramètres de positionnement
* la moyenne arithmétique(Xbar)=la somme de ni * xi divisée par N

* Médiane(Xmed)= est le plus petit xi dont son Ni est supérieur à N / 2; pour l'exemple ci-dessus Xmed = x4 = 11 car N4 = 435 est le
   plus petite valeur qui est plus grande que N / 2 = 350.

* Mode(Xmode)=est un xi dont son ni apparaît le plus souvent; pour l'exemple ci-dessus Xmod = x4 = 11 car n4 est la plus grande valeur.


* Utilisez cette option lorsque vous souhaitez montrer comment une réponse moyenne ou la plus communément indiquée

3. Mesures de dispersion ou de variation

* L'étendu e(X)=si nmax est le plus grand ni et nmin dans le plus petit donc e(X) = nmax-nmin

* Variance(V(x))=la somme de ni*(xi-Xbar)^2)/N (0<=i<=p)

* L'ecart_type (la racine carrée de la variance V(x) e(x)=sqrt(V(x))

*L'ecart_type moyen E(x)=la somme de ni*|xi-Xbar| (0<=i<=p)

* Identifie la répartition des scores en indiquant les intervalles

* Utilisez cette option lorsque vous souhaitez montrer comment les données sont "réparties". Il est utile de savoir quand vos données sont tellement dispersées qu'elles affectent la moyenne