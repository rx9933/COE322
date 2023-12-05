# Name: Arushi Sadam & Nicole Olvera 
# UT EID: ars7724 & no4342   
#  TACC ID: rx9933 & nicoleolv

# Python visualization code. Takes output data from txt files (that are output by C++ program) and creates route plots.

import matplotlib 
matplotlib.use('TKAgg')

import matplotlib.pyplot as plt
from matplotlib.collections import LineCollection
def plot(line, color):

    coordinates = []
    print(line)
        # Remove parentheses and split into pairs of coordinates
    data = line.split(": ")[1]
    adrList = data.split("), ")
# pairs = data.split(", ")
    xData = []
    yData = []
    print(adrList)
    for adr in adrList[:-1]:
        adrData = adr[1:]
        coorData = adrData.split(", ")

        xData.append(int(coorData[0]))
        yData.append(int(coorData[1]))
    print(xData)
    print(yData)
    for i in range(len(xData)-1):
        if xData[i+1]-xData[i]==0 and yData[i+1]-yData[i] ==0:
            continue
        if i==0:
            # lineW+=3
            # al+=.2 length_includes_head = True,
            # ax.arrow(xData[i], yData[i],xData[i+1]-xData[i],yData[i+1]-yData[i],
            #         head_width=0.05, head_length=0.1, fc=color, ec=color,linewidth=lineW, alpha = al, 
            #         linestyle = "--")


            ax.quiver(xData[i], yData[i], xData[i+1]-xData[i],yData[i+1]-yData[i], angles="xy", zorder=5, pivot="tail", color = color, width=.004, headwidth=5, minshaft  = .2)
            ax.quiver(xData[i+1], yData[i+1], xData[i+1]-xData[i],yData[i+1]-yData[i], angles="xy", zorder=5, pivot="tip", color = color,width=.004, headwidth=5, minshaft  = .2)
            ax.arrow(xData[i], yData[i],xData[i+1]-xData[i],yData[i+1]-yData[i],color = color,
                    linestyle = ":")    
            # # lineW-=3
            # al-=.2
        else:
            # ax.arrow(xData[i], yData[i],xData[i+1]-xData[i],yData[i+1]-yData[i],
            #     head_width=0.05, head_length=0.1, fc=color, ec=color,linewidth=lineW, alpha = al,length_includes_head = True)
            ax.arrow(xData[i], yData[i],xData[i+1]-xData[i],yData[i+1]-yData[i],color = color,
                    linestyle = "-")
            ax.quiver(xData[i], yData[i], xData[i+1]-xData[i],yData[i+1]-yData[i], angles="xy", zorder=5, pivot="tail", color = color, width=.004, headwidth=5)
            ax.quiver(xData[i+1], yData[i+1], xData[i+1]-xData[i],yData[i+1]-yData[i], angles="xy", zorder=5, pivot="tip", color = color,width=.004, headwidth=5)
             
   # plt.scatter(xData,yData,color='aquamarine', s=10) # addresses
file_path = "singleSalesmanOutput.txt"
ax = plt.axes()
with open(file_path, 'r') as file:
        lines = file.readlines()
lineno = 0
for line in lines:
    if "Greedy-Opt2 Route" in line:
        color1 = "purple"
        plot(lines[lineno+1], color1)
    # if "2 Initial" in line:
    #     color2 = "indigo"
    #     plot(lines[lineno+1], color2)

    # if "Greedy Route:" in line:
    #     color = "g"
    #     lineW=3.0
    #     al = .4
    #     plot(lines[lineno+1], color,lineW,al)
    lineno+=1
    

plt.scatter(0,0,color='black', marker = "o", s = 50) # depot
# Legend
legend_elements = [
    plt.Line2D([0], [0], marker='o', color='w', markerfacecolor="black", markersize=10, label='Depot'),
    # plt.Line2D([0], [0], linestyle='-', color='w', markerfacecolor='darkcyan', markersize=10, label='Initial Route'),
    # plt.Line2D([0], [0], linestyle=':', color='w', markerfacecolor='darkcyan', markersize=10, label='First Delivery'),
    LineCollection([[(0, 0), (1, 1)]], linewidth=1.0, alpha=1, color=color1, linestyle='-',
                   label='Greedy-Opt2 Route'),
    LineCollection([[(0, 0), (1, 1)]], linewidth=1.0, alpha=1, color=color1, linestyle=':',
                   label='First Delivery'),
    # LineCollection([[(0, 0), (1, 1)]], linewidth=1.0, alpha=1, color=color2, linestyle='-',
    #                label='Salesman 2 Initial Route'),
    # LineCollection([[(0, 0), (1, 1)]], linewidth=1.0, alpha=1, color=color2, linestyle=':',
    #                label='Salesman 2 First Delivery'),
    # plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='aquamarine', markersize=5, label='Addresses'),
   # plt.Line2D([0], [0], marker='o', color='w', markerfacecolor='g', markersize=10, label='Greedy Route'),
    ]

ax.legend(handles=legend_elements, loc='upper left',bbox_to_anchor=(1.05, 1))
# ax.legend(loc='center right', bbox_to_anchor=(1.25, 0.5))
# ax.legend(handles=legend_elements)
plt.grid(c="gray", linestyle = "--", alpha=.6)
plt.xlabel("Address X Coordinate (arbitrary length units)")
plt.ylabel("Address Y Coordinate (arbitrary length units)")
plt.title('One Salesman: Greedy-Opt2 Route')
plt.tight_layout()
plt.savefig("singleGreedyOpt2.pdf")
# Show the plot
plt.show()
