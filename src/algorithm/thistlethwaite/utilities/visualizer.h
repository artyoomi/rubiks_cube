#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "../../cube_bg_model.h"
#include "../searcher.h"

class Visualizer {
public:
    // using emove = Cube_bg_model::emove;

    // struct Viz_node;
    // using Viz_node_ptr = std::shared_ptr<Viz_node>;

    // struct Viz_node {
    //     uint32_t cube_id;
    //     emove    move;

    //     Viz_node_ptr child1;
    //     Viz_node_ptr child2;
    //     Viz_node_ptr child3;
    //     Viz_node_ptr child4;
    //     Viz_node_ptr child5;
    //     Viz_node_ptr child6;
    // };

    // void _generate_dot(Viz_node_ptr root, std::ofstream &out)
    // {
    //     if (root == nullptr) return;

    //     auto form_node = [](Viz_node_ptr node, std::ofstream &out)
    //     {
    //         out << "\"" << node->cube_id << "\\n"
    //                     << "move: " << Cube_bg_model::move_name(node->move) << "\"";
    //     };

    //     if (root->left) {
    //         out << "    ";
    //         form_node(root, out);
    //         out << " -> ";
    //         form_node(root->left, out);
    //         out << ";\n";

    //         _generate_dot(root->left, out);
    //     }
    //     if (root->right) {
    //         out << "    ";
    //         form_node(root, out);;
    //         out << " -> ";
    //         form_node(root->right, out);
    //         out << ";\n";

    //         _generate_dot(root->right, out);
    //     }
    // }

    // void _generate_DOT_file(Viz_node_ptr root)
    // {
    //     std::ofstream out("graph.dot");
    //     out << "digraph Graph {\n";
    //     out << "    node [fontname=\"Liberation Mono\"];\n";

    //     // if tree is empty
    //     if (root == nullptr)
    //         out << "    null;\n";
    //     // if tree have only root element
    //     else if (root->left == nullptr && root->right == nullptr)
    //         out << "    " << root->cube_id << ";\n";
    //     // if tree have at least 2 elements
    //     else
    //         _generate_dot(root, out);

    //     out << "}\n";
    //     out.close();
    // }
};

#endif