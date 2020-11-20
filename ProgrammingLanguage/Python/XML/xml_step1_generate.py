from xml.dom.minidom import Document
import uuid

doc = Document()
ar_package_root = doc.createElement("AR-PACKAGE")
ar_package_root.setAttribute("UUID", str(uuid.uuid1()))
doc.appendChild(ar_package_root)

short_name_node = doc.createElement("SHORT-NAME")
ar_package_root.appendChild(short_name_node)

short_name_text = doc.createTextNode("Application")
short_name_node.appendChild(short_name_text)

f = open("test.xml", "w")
doc.writexml(f, indent='\t', newl='\n', addindent='\t', encoding='utf-8')
f.close()