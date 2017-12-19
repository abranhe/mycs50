import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        
        # TODO        
        
        # load positives file into self.positives
        self.positives = set()
        file = open(positives, "r")
        for line in file:
            if line[:1] != ";" and line != "\n":
                self.positives.add(line.rstrip("\n").strip())
        file.close()
        
        # load negatives file into self.negatives
        self.negatives = set()
        file = open(negatives, "r")
        for line in file:
            if line[:1] != ";" and line != "\n":
                self.negatives.add(line.rstrip("\n").strip())
        file.close()
        
        # print(self.positives) # for testing
        


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""
        
        score = 0
        # TODO
        
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        # print(tokens)   # test
        
        for w in tokens:
            ws = w.lower()
            # print(ws)     # test
            if ws in self.positives:
                score += 1
                # print("plus:{}".format(ws))    # test
            elif ws in self.negatives:
                score -= 1
                # print("neg:{}".format(ws))     # test
        return score
                
