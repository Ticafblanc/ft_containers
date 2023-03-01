/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 20:47:59 by mdoquocb          #+#    #+#             */
/*   Updated: 2023/02/28 20:48:01 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/Unit_test.hpp"

int main(int argc, char **argv){

    std::ofstream output(argv[1]);
    std::streambuf* old_cout = std::cout.rdbuf();
    std::cout.rdbuf(file.rdbuf());

    utility_test();

    std::cout.rdbuf(old_cout);
}


int main() {

    // exécuter la fonction
    maFonction(42, 3.14);

    // restaurer le flux cout original
    std::cout.rdbuf(old_cout);

    // comparer le contenu du fichier avec une valeur attendue
    std::ifstream expected("attendu.txt");
    std::ifstream actual("resultat.txt");
    if (expected && actual) {
        std::string expected_line, actual_line;
        while (std::getline(expected, expected_line) && std::getline(actual, actual_line)) {
            if (expected_line != actual_line) {
                std::cout << "Les résultats ne correspondent pas." << std::endl;
                return 1; // sortie avec une erreur
            }
        }
        std::cout << "Les résultats correspondent." << std::endl;
        return 0; // sortie avec succès
    }
    else {
        std::cout << "Erreur lors de l'ouverture des fichiers." << std::endl;
        return 1; // sortie avec une erreur
    }
}
