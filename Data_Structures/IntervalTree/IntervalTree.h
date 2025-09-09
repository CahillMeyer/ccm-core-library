//---------------------------------------------------------------------------

#ifndef IntervalTreeH
#define IntervalTreeH

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <utility>

#include <sstream>

/**
 * @struct Interval
 * @brief Represents an interval with a low and high bound.
 */
template <typename T>
struct Interval
{
  T low; ///< The lower bound of the interval.
  T high; ///< The upper bound of the interval.

  /**
   * @brief Default constructor initializes the interval to an empty or invalid state.
   * This could represent an interval where the lower bound is greater than the upper bound.
   */
  Interval() : low(T()), high(T()) {}

  /**
   * @brief Constructs an Interval with specified low and high bounds.
   * @param l The lower bound.
   * @param h The upper bound.
   */
  Interval(T l, T h) : low(l), high(h) {}

  // You could add comparison operators or other utility methods depending on your needs.
  bool operator<(const Interval<T>& other) const {
    return this->high < other.low;
  }
  bool operator>(const Interval<T>& other) const {
    return this->low > other.high;
  }
};

/**
 * @tparam T The type of data stored in the node.
 * @struct Node
 * @brief Represents a node in the interval tree.
 */
template <typename T>
struct Node
{
  Interval<T> interval; ///< The interval associated with this node.
  T max; ///< The maximum value in the subtree (to help with overlap checks).
  std::shared_ptr<Node<T>> left; ///< Pointer to the left child node.
  std::shared_ptr<Node<T>> right; ///< Pointer to the right child node.
  std::shared_ptr<T> data; ///< Pointer to hold the data of type T.

  /**
   * @brief Constructs a Node with a given interval and optional data.
   * @param i The interval for this node.
   * @param d Optional data associated with the interval.
   */
  Node(Interval<T> i, std::shared_ptr<T> d = nullptr)
    : interval(i), max(i.high), left(nullptr), right(nullptr), data(d) {}
};

/**
 * @tparam T The type of data stored in the interval tree.
 * @class IntervalTree
 * @brief Represents an interval tree for managing intervals.
 */
template <typename T = int>
class IntervalTree
{
  public:
    IntervalTree() : Root(nullptr), size(0) {} ///< Constructs an empty IntervalTree.

    void Insert(T low, T high, std::shared_ptr<T> data = nullptr); ///< Inserts a new interval into the tree.
    void Insert(Interval<T> i, std::shared_ptr<T> data = nullptr); ///< Inserts a new interval into the tree.
    void Remove(Interval<T> i); ///< Removes an interval from the tree.
    void Update(Interval<T> oldInterval, Interval<T> newInterval, std::shared_ptr<T> newData = nullptr); ///< Updates an interval.

    /**
     * @brief Finds all intervals that contain a specific value.
     * @param value The value to check for containment.
     * @return A vector of intervals that contain the specified value.
     */
    std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > Containing(T value) const;

    /**
     * @brief Finds all intervals that overlap with a given range.
     * @param low The lower bound of the range.
     * @param high The upper bound of the range.
     * @return A vector of intervals that overlap with the specified range.
     */
    std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > Overlapping(T low, T high) const;

    /**
     * @brief Finds the maximum high value of all intervals that overlap with a given range.
     * @param low The lower bound of the range.
     * @param high The upper bound of the range.
     * @return The maximum high value of the intervals that overlap with the specified range.
     */
		T MaxHighOverlapping(T low, T high) const;

    /**
     * @brief Finds all intervals within a specific minimum and maximum range.
     * @param min The minimum value.
     * @param max The maximum value.
     * @return A vector of intervals that fall within the specified range.
     */
    std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > FindByMinMax(T min, T max) const;


    /**
     * @brief Checks if a specific value is contained within any interval.
     * @param value The value to check.
     * @return True if the value is contained in any interval, false otherwise.
     */
    bool Contains(T value) const;

    /**
     * @brief Checks if any intervals overlap with a given range.
     * @param low The lower bound of the range.
     * @param high The upper bound of the range.
     * @return True if there are overlapping intervals, false otherwise.
     */
    bool Overlaps(T low, T high) const;

    /**
     * @brief Clears the entire interval tree.
     */
    void Clear(void);

    /**
     * @brief Checks whether the tree is empty.
     * @return True if the tree is empty, false otherwise.
     */
    bool IsEmpty(void) const;

    /**
     * @brief Converts the interval tree to a string representation.
     *
     * This method performs an in-order traversal of the tree and
     * constructs a string that lists all the intervals in ascending
     * order.
     *
     * @return A string representation of the intervals in the tree.
     */
    std::string ToString() const;

    /**
     * @brief Gets the number of intervals in the tree.
     *
     * This method returns the count of intervals currently stored
     * in the interval tree.
     *
     * @return The number of intervals in the tree.
     */
    size_t Size() const;

  private:
    std::shared_ptr<Node<T> > Root;  ///< The root of the interval tree.
    size_t size; ///< The number of intervals in the tree.

    /**
     * @brief Helper function to insert an interval.
     */
    std::shared_ptr<Node<T> > Insert(std::shared_ptr<Node<T> > node, Interval<T> i, std::shared_ptr<T> data);

    /**
     * @brief Helper function to remove an interval.
     */
    std::shared_ptr<Node<T> > Remove(std::shared_ptr<Node<T> > node, Interval<T> i);

    /**
     * @brief Updates the maximum values in the subtree.
     */
    void UpdateMax(std::shared_ptr<Node<T> > node);

    /**
     * @brief UFinds the minimum node in the subtree.
     */
    std::shared_ptr<Node<T> > FindMin(std::shared_ptr<Node<T> > node) const;

    /**
     * @brief Finds intervals containing a specific value.
     */
    void FindContaining(std::shared_ptr<Node<T> > node, T value,
      std::vector<std::pair<Interval<T>, std::shared_ptr<T> > >& result) const;

    /**
     * @brief Finds overlapping intervals with a given range.
     */
    void FindOverlapping(std::shared_ptr<Node<T> > node, T low, T high,
      std::vector<std::pair<Interval<T>, std::shared_ptr<T> > >& result) const;

    /**
     * @brief Finds the max high value of the overlapping intervals with a given range.
     */
    void MaxHighOverlapping(std::shared_ptr<Node<T>> node, T low, T high, T& maxValue) const;

    /**
     * @brief Finds intervals within a specific range.
     */
    void FindByMinMax(std::shared_ptr<Node<T> > node, T min, T max,
      std::vector<std::pair<Interval<T>, std::shared_ptr<T> > >& result) const;

    /**
     * @brief Checks if a value is contained in the tree.
     */
    bool Contains(std::shared_ptr<Node<T>> node, T value) const;

    /**
     * @brief Checks for overlaps in the tree.
     */
    bool Overlaps(std::shared_ptr<Node<T>> node, T low, T high) const;

    /**
     * @brief Calculates the height of the subtree rooted at the given node.
     */
    int Height(std::shared_ptr<Node<T>> node) const;

    /**
     * @brief Calculates the balance factor of the given node.
     */
    int GetBalance(std::shared_ptr<Node<T>> node) const;

    /**
     * @brief Performs a right rotation on the given node.
     */
    std::shared_ptr<Node<T>> RotateRight(std::shared_ptr<Node<T>> node);

    /**
     * @brief Performs a left rotation on the given node.
     */
    std::shared_ptr<Node<T>> RotateLeft(std::shared_ptr<Node<T>> node);

    void ToString(std::shared_ptr<Node<T>> node, std::ostringstream& oss) const;
};


template <typename T>
void IntervalTree<T>::Insert(T low, T high, std::shared_ptr<T> data)
{
  Interval<T> i(low, high);
  Insert(i, data);
}

template <typename T>
void IntervalTree<T>::Insert(Interval<T> i, std::shared_ptr<T> data)
{
  if(i.low > i.high)
  {
    throw std::invalid_argument("Invalid interval: low must be less than or equal to high.");
  }
  Root = Insert(Root, i, data);
  size++; // Increment size on successful insertion
}

template <typename T>
void IntervalTree<T>::Remove(Interval<T> i)
{
    if(Contains(i.low)) // Optional: Check if interval exists before removing
    {
        Root = Remove(Root, i);
        size--; // Decrement size on successful removal
    }
}

template <typename T>
void IntervalTree<T>::Update(Interval<T> oldInterval, Interval<T> newInterval, std::shared_ptr<T> newData)
{
  Remove(oldInterval);
  Insert(newInterval, newData);
}

template <typename T>
std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > IntervalTree<T>::Containing(T value) const
{
  std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > result;
  FindContaining(Root, value, result);
  return result;
}

template <typename T>
std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > IntervalTree<T>::Overlapping(T low, T high) const
{
  std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > result;
  FindOverlapping(Root, low, high, result);
  return result;
}

template <typename T>
T IntervalTree<T>::MaxHighOverlapping(T low, T high) const
{
  T maxValue = std::numeric_limits<T>::min();  // Initialize to the smallest possible value of type T.
  MaxHighOverlapping(Root, low, high, maxValue);   // Call the helper function to compute the max value.
  return maxValue;
}

template <typename T>
std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > IntervalTree<T>::FindByMinMax(T min, T max) const
{
  std::vector<std::pair<Interval<T>, std::shared_ptr<T> > > result;
  FindByMinMax(Root, min, max, result);
  return result;
}

template <typename T>
bool IntervalTree<T>::Contains(T value) const
{
  return Contains(Root, value);
}

template <typename T>
bool IntervalTree<T>::Overlaps(T low, T high) const
{
  return Overlaps(Root, low, high);
}

template <typename T>
void IntervalTree<T>::Clear()
{
  Root = nullptr; // Setting the root to nullptr will clear the entire tree.
  size = 0;
}

template <typename T>
size_t IntervalTree<T>::Size() const
{
  return size; // Return the current size of the tree
}

template <typename T>
bool IntervalTree<T>::IsEmpty() const
{
  return Root == nullptr;
}

template <typename T>
std::string IntervalTree<T>::ToString() const
{
  std::ostringstream oss;
  // In-order traversal to print intervals
  ToString(Root, oss);
  return oss.str();
}

template <typename T>
std::shared_ptr<Node<T> > IntervalTree<T>::Insert(std::shared_ptr<Node<T> > node, Interval<T> i, std::shared_ptr<T> data)
{
  if(node == nullptr)
  {
    return std::make_shared<Node<T> >(i, data);
  }

  if(i.low < node->interval.low)
  {
    node->left = Insert(node->left, i, data);
  }
  else
  {
    node->right = Insert(node->right, i, data);
  }

  UpdateMax(node);

  // Check for balance and perform rotations if needed
  int balance = GetBalance(node);
  if(balance > 1)
  {
    if(i.low < node->left->interval.low)
    {
      return RotateRight(node);
    }
    else
    {
      node->left = RotateLeft(node->left);
      return RotateRight(node);
    }
  }
  if(balance < -1)
  {
    if(i.low > node->right->interval.low)
    {
      return RotateLeft(node);
    }
    else
    {
      node->right = RotateRight(node->right);
      return RotateLeft(node);
    }
  }
  return node;
}

template <typename T>
std::shared_ptr<Node<T> > IntervalTree<T>::Remove(std::shared_ptr<Node<T> > node, Interval<T> i)
{
  if(node == nullptr)
  {
    return nullptr;
  }

  if(i.low < node->interval.low)
  {
    node->left = Remove(node->left, i);
  }
  else if(i.low > node->interval.low)
  {
    node->right = Remove(node->right, i);
  }
  else
  {
    // Node with the interval found
    if(node->left == nullptr)
    {
      return node->right;
    }
    else if(node->right == nullptr)
    {
      return node->left;
    }

    // Node with two children: Get the inorder successor (smallest in the right subtree)
    std::shared_ptr<Node<T> > minNode = FindMin(node->right);
    node->interval = minNode->interval;
    node->data = minNode->data;
    node->right = Remove(node->right, minNode->interval);
  }

  UpdateMax(node);
  return node;
}

template <typename T>
void IntervalTree<T>::UpdateMax(std::shared_ptr<Node<T> > node)
{
  if(node)
  {
    node->max = node->interval.high;
    if(node->left)
    {
      node->max = std::max(node->max, node->left->max);
    }
    if(node->right)
    {
      node->max = std::max(node->max, node->right->max);
    }
  }
}

template <typename T>
std::shared_ptr<Node<T> > IntervalTree<T>::FindMin(std::shared_ptr<Node<T> > node) const
{
  while(node && node->left)
  {
    node = node->left;
  }
  return node;
}

template <typename T>
void IntervalTree<T>::FindContaining(std::shared_ptr<Node<T>> node, T value,
  std::vector<std::pair<Interval<T>, std::shared_ptr<T>>>& result) const
{
  if(node == nullptr)
  {
    return;
  }

  // Check if the current node's interval contains the value
  if(node->interval.low <= value && node->interval.high >= value)
  {
    result.emplace_back(node->interval, node->data);
  }

  // Traverse the left subtree if it might contain intervals
  if(node->left && node->left->max >= value)
  {
    FindContaining(node->left, value, result);
  }

  // Always traverse the right subtree
  FindContaining(node->right, value, result);
}

template <typename T>
void IntervalTree<T>::FindOverlapping(std::shared_ptr<Node<T> > node, T low, T high,
  std::vector<std::pair<Interval<T>, std::shared_ptr<T> > >& result) const
{
  if(node == nullptr)
  {
    return;
  }

  if(node->interval.low <= high && node->interval.high >= low)
  {
    result.emplace_back(node->interval, node->data);
  }

  if(node->left && node->left->max >= low)
  {
    FindOverlapping(node->left, low, high, result);
  }

  FindOverlapping(node->right, low, high, result);
}

template <typename T>
void IntervalTree<T>::MaxHighOverlapping(std::shared_ptr<Node<T>> node, T low, T high, T& maxValue) const
{
  if (node == nullptr)
  {
    return;
  }

  // Check if the current node's interval overlaps with the given range.
  if (node->interval.low <= high && node->interval.high >= low)
  {
    // If it overlaps, update the max value with the "high" value of the current node's interval.
    maxValue = std::max(maxValue, node->interval.high);
  }

  // Prune the search based on the maximum value of the left child (if any).
  if (node->left && node->left->max >= low)
  {
    MaxHighOverlapping(node->left, low, high, maxValue);  // Check the left subtree.
  }

  // Always check the right subtree (since overlapping intervals can be in both directions).
  MaxHighOverlapping(node->right, low, high, maxValue);
}

template <typename T>
void IntervalTree<T>::FindByMinMax(std::shared_ptr<Node<T> > node, T min, T max,
  std::vector<std::pair<Interval<T>, std::shared_ptr<T> > >& result) const
{
  if(node == nullptr)
  {
    return;
  }

  if(node->interval.high >= min && node->interval.low <= max)
  {
    result.emplace_back(node->interval, node->data);
  }

  FindByMinMax(node->left, min, max);
  FindByMinMax(node->right, min, max);
}

template <typename T>
bool IntervalTree<T>::Contains(std::shared_ptr<Node<T>> node, T value) const
{
  if(node == nullptr)
  {
    return false; // No interval found
  }

  // Check if the current node's interval contains the value
  if(node->interval.low <= value && node->interval.high >= value)
  {
    return true; // Found a containing interval
  }

  // Traverse the left subtree if it might contain the value
  if(node->left && node->left->max >= value)
  {
    return Contains(node->left, value);
  }

  // Always check the right subtree
  return Contains(node->right, value);
}

template <typename T>
bool IntervalTree<T>::Overlaps(std::shared_ptr<Node<T>> node, T low, T high) const
{
  if(node == nullptr)
  {
    return false;
  }

  if(node->interval.low <= high && node->interval.high >= low)
  {
    return true;
  }

  if(node->left && node->left->max >= low)
  {
    return Overlaps(node->left, low, high);
  }

  return Overlaps(node->right, low, high);
}

template <typename T>
int IntervalTree<T>::Height(std::shared_ptr<Node<T>> node) const
{
    if(node == nullptr)
    {
        return 0;
    }
    return 1 + std::max(Height(node->left), Height(node->right));
}

template <typename T>
int IntervalTree<T>::GetBalance(std::shared_ptr<Node<T>> node) const
{
    if(node == nullptr)
    {
        return 0;
    }
    return Height(node->left) - Height(node->right);
}

template <typename T>
std::shared_ptr<Node<T>> IntervalTree<T>::RotateRight(std::shared_ptr<Node<T>> node)
{
    std::shared_ptr<Node<T>> newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    // Update the max value of the rotated nodes
    UpdateMax(node);
    UpdateMax(newRoot);

    return newRoot; // New root of the subtree
}

template <typename T>
std::shared_ptr<Node<T>> IntervalTree<T>::RotateLeft(std::shared_ptr<Node<T>> node)
{
    std::shared_ptr<Node<T>> newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    // Update the max value of the rotated nodes
    UpdateMax(node);
    UpdateMax(newRoot);

    return newRoot; // New root of the subtree
}

template <typename T>
void IntervalTree<T>::ToString(std::shared_ptr<Node<T>> node, std::ostringstream& oss) const
{
  if(node)
  {
    ToString(node->left, oss);
    oss << "[" << node->interval.low << ", " << node->interval.high << "] ";
    ToString(node->right, oss);
  }
}
#endif

