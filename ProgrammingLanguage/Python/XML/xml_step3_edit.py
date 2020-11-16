#coding=utf-8
from xml.dom import minidom
import uuid

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

ar_package_node = doc.createElement("AR-PACKAGE")
ar_package_node.setAttribute("UUID", str(uuid.uuid1()))
node.appendChild(ar_package_node)
short_name_node = doc.createElement("SHORT-NAME")
ar_package_node.appendChild(short_name_node)
short_name_text.createTextNode("ApplicationDeployment")
short_name_node.appendChild(short_name_text)

f = open("test.xml", "w")
doc.writexml(f, indent='\t', newl='\n', addindent='\t', encoding='utf-8')
f.close()