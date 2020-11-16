#coding=utf-8
from xml.dom import minidom

doc = minidom.parse("test.xml")
root = doc.documentElement
print("Node name: ", root.nodeName)
print("Node UUID: ", root.getAttribute("UUID"))

def findARPackageNodeByShortName(node, short_name):
    if (node.nodeName == "AR-PACKAGE"):
        for child_node in node.childNodes:
            if (child_node.nodeName == "SHORT-NAME"):
                if (child_node.childNodes[0].data == short_name):
                    return node
            else:
                target_node = findARPackageNodeByShortName(child_node, short_name)
                if (target_node):
                    return target_node
    else:
        for child_node in node.childNodes:
            target_node = findARPackageNodeByShortName(child_node, short_name)
            if (target_node):
                return target_node

node = findARPackageNodeByShortName(root, "Application")
print("Node name: ", node.nodeName)
print("Node text: ", node.getElementByTagName("SHORT-NAME"),childNodes[0].data)